#include "util.h"

#include <iostream>

int main() {
  cl::Platform default_platform = clutil::GetDefaultPlatform();
  std::cout << "Using platform: "
	    << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

  // get default device (CPUs, GPUs) of the default platform
  std::vector<cl::Device> all_devices = clutil::GetPlatformDevices(default_platform);

  if (all_devices.size() == 0) {
    std::cout << " No devices found. Check OpenCL installation!\n";
    exit(1);
  }

  cl::Device default_device = all_devices[0];
  std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>()
	    << "\n";

  // calculates for each element; C = A + B
  std::string kernel_code =
      "   void kernel simple_add(global const int* A, global const int* B, "
      "global int* C, "
      "                          global const int* N) {"
      "       int ID, Nthreads, n, ratio, start, stop;"
      ""
      "       ID = get_global_id(0);"
      "       Nthreads = get_global_size(0);"
      "       n = N[0];"
      ""
      "       ratio = (n / Nthreads);"  // number of elements for each thread
      "       start = ratio * ID;"
      "       stop  = ratio * (ID + 1);"
      ""
      "       for (int i=start; i<stop; i++)"
      "           C[i] = A[i] + B[i];"
      "   }";

	auto compilation_units = clutil::Compile(default_device, {kernel_code});
	cl::Context& context = std::get<0>(compilation_units);
	cl::Program& program = std::get<1>(compilation_units);

  if (program.build({default_device}) != CL_SUCCESS) {
    std::cout << "Error building: "
	      << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)
	      << std::endl;
    exit(1);
  }

  // apparently OpenCL only likes arrays ...
  // N holds the number of elements in the vectors we want to add
  int N[1] = {10000};
  int n = N[0];

  // create buffers on device (allocate space on GPU)
  cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_N(context, CL_MEM_READ_ONLY, sizeof(int));

  // create things on here (CPU)
  int A[n], B[n];
  for (int i = 0; i < n; i++) {
    A[i] = i;
    B[i] = n - i - 1;
  }
  // create a queue (a queue of commands that the GPU will execute)
  cl::CommandQueue queue(context, default_device);

  // push write commands to queue
  queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * n, A);
  queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * n, B);
  queue.enqueueWriteBuffer(buffer_N, CL_TRUE, 0, sizeof(int), N);

  // RUN ZE KERNEL
  cl::Kernel simple_add(program, "simple_add");
  simple_add.setArg(0, buffer_A);
  simple_add.setArg(1, buffer_B);
  simple_add.setArg(2, buffer_C);
  simple_add.setArg(3, buffer_N);
  queue.enqueueNDRangeKernel(simple_add, cl::NullRange, cl::NDRange(1000),
                             cl::NullRange);

  int C[n];
  // read result from GPU to here
  queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * n, C);

  // Now do the same calculation on the CPU.
  std::cout << "Cross-verifying CPU and GPU vector sum..." << std::endl;
  for (int i = 0; i < n; i++) {
    if (C[i] != A[i] + B[i]) {
      std::cout << "Failed @ C[" << i << "]. " << C[i] << " != " << A[i] << " + " << B[i] << "!";
      return 1;
    }
  }
  std::cout << "Cross-verified. PASS." << std::endl;
  return 0;
}
