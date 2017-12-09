cc_library(
    name = "util",
    visibility = ["//opencl"],
    hdrs = ["util.h"],
    deps = [],
)

cc_binary(
    name = "cltest",
    visibility = ["//opencl"],
    srcs = ["cltest.cc"],
    copts = [
      "--std=c++1z",
    ],
    linkopts = [
        "-lOpenCL",
    ],
    deps = [
        ":util",
    ],
)

package_group(
    name = "opencl",
    packages = [
        "//opencl/...",
    ],
    includes = [
        ":opencl_users",
    ],
)

package_group(
    name = "opencl_users",
    packages = [
        "//math/..."
    ],
    includes = [],
)
