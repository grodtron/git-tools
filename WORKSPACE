load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
  name = "com_google_googletest",
  commit = "e2239ee6043f73722e7aa812a459f54a28552929", # 1.11.0
  shallow_since = "1623433346 -0700",
  remote = "https://github.com/google/googletest.git",
  patches = [
    # Remove import of abseil (we can use our own), below
    "//third_party:patches/com_google_googletest/WORKSPACE.patch"
  ]
)

git_repository(
  name = "range-v3",
  shallow_since = "1596755110 -0600",
  commit = "4989f3e9ff2efee1852942bb9328ef121369ba02", # 0.11.0
  remote = "https://github.com/ericniebler/range-v3.git",
)

git_repository(
  name = "com_github_google_benchmark",
  shallow_since = "1623228732 +0300",
  commit = "e991355c02b93fe17713efe04cbc2e278e00fdbd", # v1.5.5
  remote = "https://github.com/google/benchmark.git"
)

git_repository(
  name = "com_google_absl",
  commit = "278e0a071885a22dcd2fd1b5576cc44757299343", # Abseil LTS 20210324, Patch 2
  remote = "https://github.com/abseil/abseil-cpp.git",
  patches = [
    # Remove imports of gtest and gmock, use these ones
    "//third_party:patches/com_google_absl/WORKSPACE.patch"
  ]
)

new_git_repository(
  name = "libgit2",
  commit = "172239021f7ba04fe7327647b213799853a9eb89",
  # remote = "/home/gordon/libgit2",
  shallow_since = "1582108020 +0100",
  remote = "https://github.com/libgit2/libgit2.git",
  build_file = "@//third_party:BUILD.libgit2",
  patches = [
    "//third_party:patches/libgit2/features.h.patch",
    "//third_party:patches/libgit2/pcre.config.h.patch",
  ]
)

new_git_repository(
  name = "termcolor",
  commit = "67eb0aa55e48ead9fe2aab049f0b1aa7943ba0ea",
  remote = "https://github.com/ikalnytskyi/termcolor",
  build_file = "@//third_party:BUILD.termcolor",
  shallow_since = "1614533514 +0200"
)

new_git_repository(
  name = "fmt",
  commit = "9e8b86fd2d9806672cc73133d21780dd182bfd24", # 8.0.0
  remote = "https://github.com/fmtlib/fmt.git",
  build_file = "@//third_party:BUILD.fmt"
)
