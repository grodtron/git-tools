#include <filesystem>
#include <iostream>

#include "termcolor/termcolor.hpp"

#include "git2.h"

#include "git3/repo.hh"

int main(int argc, const char *argv[]) {
  git_libgit2_init();  // TODO
  // NOTE: this doesn't work when running under Bazel, cause it
  // finds the crazy bazel directory
  // const auto pwd = std::filesystem::current_path();
  //
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path-to-git-repo>" << std::endl;
    return 1;
  }

  const std::string pwd = argv[1];

  auto repo = g3::Repo::open(pwd.c_str());

  for (const auto b : repo.branches()) {
    const auto upstream = b.upstream();
    std::cout << b.name() << "(" << b.commit().hash() << ")"
              << " -> " << termcolor::yellow
              << (upstream ? upstream.name() : "None") << termcolor::reset
              << ")" << std::endl;

    if (upstream) {
      const auto aheadBehind = repo.aheadBehind(b, upstream);

      std::cout << "  " << termcolor::green << termcolor::bold << "+"
                << aheadBehind.ahead << termcolor::reset << "|"
                << termcolor::red << termcolor::bold << "-"
                << aheadBehind.behind << termcolor::reset << std::endl;
    }
  }
}
