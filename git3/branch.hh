#pragma once

#include <memory>
#include <string>

#include "git2.h"

namespace g3 {

class Branch {
 public:
  Branch(git_reference* branch) : branch_(branch, git_reference_free) {}

  std::string name() const {
    const char* n = nullptr;

    git_branch_name(&n, branch_.get());

    return n;
  }

 private:
  std::unique_ptr<git_reference, decltype(&git_reference_free)> branch_;
};

}  // namespace g3
