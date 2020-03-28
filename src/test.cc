#include <filesystem>
#include <iostream>

#include "git2.h"

#include "git3/repo.hh"

int main(int argc, const char *argv[]) {
  git_libgit2_init();  // TODO
  // const auto pwd = std::filesystem::current_path();
  const std::string pwd = argv[1];

  auto repo = g3::Repo::open(pwd.c_str());

  for (const auto b : repo.branches()) {
    std::cout << b.name() << std::endl;
  }
}
