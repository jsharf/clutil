cc_library(
    name = "util",
    visibility = ["//visibility:public"],
    defines = ["CL_TARGET_OPENCL_VERSION=220"],
    hdrs = ["util.h"] + glob(["CL/*"]),
    srcs = ["util.cc"],
    deps = [],
)

config_setting(
    name = "linux",
    visibility = ["//visibility:public"],
    constraint_values = [
      "@bazel_tools//platforms:linux",
    ],
)

config_setting(
    name = "osx",
    visibility = ["//visibility:public"],
    constraint_values = [
      "@bazel_tools//platforms:osx",
    ],
)

cc_binary(
    name = "cltest",
    visibility = ["//visibility:private"],
    srcs = ["cltest.cc"],
    copts = [
      "--std=c++1z",
    ],
    linkopts = select({
        ":osx" : ["-framework OpenCL"],
        ":linux" : ["-lOpenCL", "-L/usr/local/cuda-8.0/targets/x86_64-linux/lib"],
        "//conditions:default" : ["-lOpenCL", "-L/usr/local/cuda-8.0/targets/x86_64-linux/lib"],
    }),
    deps = [
        ":util",
    ],
)

package_group(
    name = "clutil",
    packages = [
        "//clutil/...",
    ],
)
