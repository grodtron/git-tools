#pragma once

#include <string>

#include "git2.h"

namespace g3 {

class Commit {
 public:
  Commit(const git_oid* oid) : oid_(oid) {}

  std::string hash() const { return git_oid_tostr_s(oid_); }

 private:
  const git_oid* oid_;
};

}  // namespace g3
