#pragma once

#include <string>

#include "git3/branch_iteration.hh"
#include "git3/pointer_types.hh"

namespace g3 {

class Repo {
 public:
  static Repo open(std::string path);

  BranchRange branches() const;

 private:
  Repo(git_repository *r) : repo_(r) {}

  g3::unique_ptr<git_repository> repo_;
};

}  // namespace g3
