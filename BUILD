cc_library(
    name = "util",
    visibility = ["//clutil"],
    hdrs = ["util.h"] + glob(["CL/*"]),
    deps = [],
)

cc_binary(
    name = "cltest",
    visibility = ["//clutil"],
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
