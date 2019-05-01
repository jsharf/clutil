#ifndef UTIL_H
#define UTIL_H

//  Unfortunately opencl injects annoying warnings, so this is a temporary
//  countermeasure.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wignored-attributes"
#include "clutil/CL/cl.hpp"
#pragma GCC diagnostic pop

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace clutil {

std::vector<cl::Platform> GetPlatforms();

// Naively chooses platform 0 as the default.
cl::Platform GetDefaultPlatform();

std::vector<cl::Device> GetPlatformDevices(const cl::Platform& platform);

// Compile a list of sources under the same context for a given device.
std::tuple<cl::Context, cl::Program> Compile(
    const cl::Device& device, const std::vector<std::string>& source_strings);

}  // namespace clutil
#endif /* UTIL_H */
