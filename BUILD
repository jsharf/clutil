cc_library(
    name = "util",
    visibility = ["//clutil"],
    hdrs = ["util.h"] + glob(["CL/*"]),
    srcs = ["util.cc"],
    deps = [],
)

config_setting(
    name = "linux",
    visibility = ["//clutil"],
    constraint_values = [
      "@bazel_tools//platforms:linux",
    ],
)

config_setting(
    name = "osx",
    visibility = ["//clutil"],
    constraint_values = [
      "@bazel_tools//platforms:osx",
    ],
)

cc_binary(
    name = "cltest",
    visibility = ["//clutil"],
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
    includes = [
        ":clutil_users",
    ],
)

package_group(
    name = "clutil_users",
    packages = [
        "//math/..."
    ],
    includes = [],
)
