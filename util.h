#ifndef UTIL_H
#define UTIL_H

//  Unfortunately opencl injects annoying warnings, so this is a temporary
//  countermeasure.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "clutil/CL/cl.hpp"
#pragma GCC diagnostic pop

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace clutil {

std::vector<cl::Platform> GetPlatforms() {
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (all_platforms.size() == 0) {
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
  platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
  if (devices.size() == 0) {
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
              << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device)
              << std::endl;
    std::exit(1);
  }
  return std::make_tuple(context, program);
}

}  // namespace clutil
#endif /* UTIL_H */
