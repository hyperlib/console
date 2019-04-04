licenses(["notice"]) # MIT

exports_files(["LICENSE.md"])

cc_library(
    name = "hyperconsole",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["include/**/*.hpp"]),
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "hyperconsole-test",
    srcs = glob(["test/**/*.cpp"]),
    copts = ["-Iinclude -I/usr/local/include"],
    deps = [
        ":hyperconsole"
    ]
)
