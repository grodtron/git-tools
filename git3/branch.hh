#pragma once

#include <string>

#include "git3/commit.hh"
#include "git3/pointer_types.hh"

#include "git2.h"

namespace g3 {

class Branch {
 public:
  Branch(git_reference* branch) : branch_(branch) {}

  explicit operator bool() const { return static_cast<bool>(branch_); }

  std::string name() const {
    const char* n = nullptr;

    const auto result = git_branch_name(&n, branch_.get());

    if (result == GIT_EINVALID) {
      // TODO how do we handle this error condition?
      return "INVALID BRANCH";
    } else {
      return n;
    }
  }

  Branch upstream() const {
    git_reference* out = nullptr;

    const auto result = git_branch_upstream(&out, branch_.get());

    if (result == GIT_ENOTFOUND) {
      return Branch(nullptr);
    } else {
      return Branch(out);
    }
  }

  Commit commit() const {
    const auto oid = git_reference_target(branch_.get());

    return Commit(oid);
  }

 private:
  g3::unique_ptr<git_reference> branch_;
};

}  // namespace g3
