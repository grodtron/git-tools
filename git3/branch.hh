#pragma once

#include <string>

#include "git3/pointer_types.hh"

#include "git2.h"

namespace g3 {

class Branch {
 public:
  Branch(git_reference* branch) : branch_(branch) {}

  std::string name() const {
    const char* n = nullptr;

    git_branch_name(&n, branch_.get());

    return n;
  }

 private:
  g3::unique_ptr<git_reference> branch_;
};

}  // namespace g3
