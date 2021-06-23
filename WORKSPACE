load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
  name = "gtest",
  commit = "703bd9caab50b139428cea1aaff9974ebee5742e",
  shallow_since = "1570114335 -0400",
  remote = "https://github.com/google/googletest.git",
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

