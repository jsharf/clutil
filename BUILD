cc_library(
    name = "util",
    visibility = ["//clutil"],
    hdrs = ["util.h"] + glob(["CL/*"]),
    deps = [],
)

config_setting(
    name = "linux",
    constraint_values = [
      "@bazel_tools//platforms:linux",
    ],
)

config_setting(
    name = "osx",
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
        ":linux" : ["-lOpenCL"],
        "//conditions:default" : ["-lOpenCL"],
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
