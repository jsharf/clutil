#ifndef UTIL_H
#define UTIL_H

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <string>
#include <vector>

namespace clutil {

std::vector<cl::Platform> GetPlatforms() {
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (platforms.size() == 0) {
    std::cerr << "No platforms found. Check OpenCL Installation." << std::endl;
    std::exit(1);
  }
  return all_platforms;
}

// Naively chooses platform 0 as the default.
cl::Platform GetDefaultPlatform() {
  auto platforms = GetPlatforms();
  if (platforms.size() == 0) {
    std::cerr << "No platforms found. Check OpenCL Installation." << std::endl;
    std::exit(1);
  }
  return platforms[0];
}

std::vector<cl::Device> GetPlatformDevices(const cl::Platform& platform) {
  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
  if (all_devices.size() == 0) {
    std::cout << " No devices found. Check OpenCL installation!\n";
    exit(1);
  }
  return devices;
}

// Compile a list of sources under the same context for a given device.
std::tuple<cl::Context, cl::Program> Compile(
    const cl::Device& device, const std::vector<std::string>& source_strings) {
  cl::Context context({device});

  cl::Program::Sources sources;
  for (const auto& source : source_strings) {
    sources.push_back({source.c_str(), source.size()});
  }

  cl::Program program(context, sources);
  if (program.build({device}) != CL_SUCCESS) {
    std::cout << "Error building: "
              << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)
              << std::endl;
    std::exit(1);
  }
  return std::make_tuple(context, program);
}

}  // namespace clutil
#endif /* UTIL_H */
