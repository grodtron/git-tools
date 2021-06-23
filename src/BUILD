cc_binary(
  name = "test",
  srcs = ["test.cc"],
  deps = ["@libgit2//:git2", "//git3:git3", "@termcolor//:termcolor"],
  copts = ["-std=c++17"],
  linkopts = ["-lstdc++fs"],
)
