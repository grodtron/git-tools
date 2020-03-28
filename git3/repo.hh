#pragma once

#include <string>

#include "git3/branch_iteration.hh"

namespace g3 {

class Repo {
 public:
  static Repo open(std::string path);

  BranchRange branches() const;

 private:
  Repo(git_repository *r) : repo_(r, git_repository_free) {}

  std::unique_ptr<git_repository, decltype(&git_repository_free)> repo_;
};

}  // namespace g3
