cc_library(
  name = "git_fixture",
  srcs = ["git_fixture.cc"],
  hdrs = ["git_fixture.hh"],
  deps = [
    "//stdx:cstdlib",
    "//git3:git3",
    "@com_google_googletest//:gtest",
    "@fmt//:fmt"
  ],
  linkopts = [
    "-lstdc++fs"
  ],
  copts = [
    "-std=c++17"
  ],
  visibility = ["//visibility:public"]
)
