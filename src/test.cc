#include <filesystem>
#include <iostream>

#include "git2.h"

int main(int argc, const char *argv[]) {
  git_libgit2_init();

  git_repository *this_repo = nullptr;

  const auto pwd = std::filesystem::current_path();

  if (git_repository_open(&this_repo, pwd.c_str())) {
    const auto error = git_error_last();
    std::cout << "Seems we're not in a git repository... (" << error->message
              << ")" << std::endl;
    return 1;
  }

  git_branch_iterator *branch_it = nullptr;

  if (int err =
          git_branch_iterator_new(&branch_it, this_repo, GIT_BRANCH_LOCAL)) {
    std::cout << "Couldn't get a branch iterator for some reason (reason is "
              << err << ")" << std::endl;
    return 2;
  }

  int status = 0;
  git_reference *branch = nullptr;
  git_branch_t branch_type;
  while (!(status = git_branch_next(&branch, &branch_type, branch_it))) {
    const char *name = nullptr;
    git_branch_name(&name, branch);

    std::cout << name << std::endl;
  }

  return 0;
}
