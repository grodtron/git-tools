#pragma once

#include <string>

#include "git3/branch.hh"
#include "git3/branch_iteration.hh"
#include "git3/commit.hh"
#include "git3/libgit2_initializer.hh"
#include "git3/pointer_types.hh"

namespace g3 {

class Repo {
 public:
  static Repo open(std::string path);
  Repo() = default;
  Repo(Repo &) = delete;
  Repo(Repo &&) = default;
  Repo &operator=(Repo &) = delete;
  Repo &operator=(Repo &&) = default;

  BranchRange branches() const;

  struct AheadBehind {
    size_t ahead;
    size_t behind;
  };

  AheadBehind aheadBehind(const Branch &local, const Branch &upstream) const;

 private:
  Repo(git_repository *r) : repo_(r) {}

  g3::unique_ptr<git_repository> repo_;
  g3::internal::Libgit2Initializer initializer_;
};

}  // namespace g3
