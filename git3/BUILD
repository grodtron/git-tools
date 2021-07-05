
cc_library(
  name = "git3",
  srcs = glob(include=["*.cc"], exclude=["*_test.cc"]),
  hdrs = glob(["*.hh"]),
  deps = [
    "//git3/exceptions:exceptions",
    "@libgit2//:git2",
    "@com_google_absl//absl/container:flat_hash_map",
    "@com_google_absl//absl/base:core_headers",
  ],
  copts = ["-std=c++17"],
  linkopts = ["-lstdc++fs"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "branch_tree_test",
  srcs = ["branch_tree_test.cc"],
  deps = [
    "//git3:git3",
    "//git3/testing:git_fixture",
    "@com_google_googletest//:gtest_main"
  ],
  copts = ["-std=c++17"],
  linkopts = ["-lstdc++fs"],
)
