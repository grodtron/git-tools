
cc_library(
  name = "git3",
  srcs = glob(["*.cc"]),
  hdrs = glob(["*.hh"]),
  deps = ["@libgit2//:git2"],
  copts = ["-std=c++17"],
  linkopts = ["-lstdc++fs"],

  visibility = ["//visibility:public"],
)
