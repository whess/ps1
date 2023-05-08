load("//:local_deploy.bzl", "local_deploy")

cc_binary(
    name = "ps1",
    srcs = ["ps1.cc"],
    deps = [
        ":ps1_lib",
        "@absl//absl/flags:flag",
        "@absl//absl/flags:parse",
    ],
)

cc_library(
    name = "ps1_lib",
    srcs = ["ps1_lib.cc"],
    hdrs = ["ps1_lib.h"],
    deps = [
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "ps1_lib_test",
    srcs = ["ps1_lib_test.cc"],
    deps = [
        ":ps1_lib",
        "@com_google_googletest//:gtest_main",
    ],
)

local_deploy(
    name = "install",
    srcs = [":ps1"],
    target = "~/bin",
)
