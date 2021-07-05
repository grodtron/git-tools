#pragma once

#include "git3/branch.hh"
#include "git3/pointer_types.hh"

#include "git2.h"

namespace g3 {

class BranchEndIterator {};

class BranchIterator {
 public:
  BranchIterator(g3::unique_ptr<git_branch_iterator>);

  BranchIterator& operator++();

  Branch operator*();

  // TODO - need to verify, is this an OK way to compare to end? Because our
  // dereference operator actually moves out the value at the current point in
  // the operation, so if we check equal to end _after_ dereferencing, then we
  // would get true.
  //
  // Is this acceptable?
  bool operator!=(const BranchEndIterator& other) {
    // If the iterator has a current branch, then it's not equal to the end
    // iterator
    return static_cast<bool>(current_branch_);
  }

 private:
  void next_();

  Branch current_branch_;

  // The git2 c-style branch iterator
  g3::unique_ptr<git_branch_iterator> g2_iterator_;
};

class BranchRange {
 public:
  BranchRange(git_branch_iterator*);

  BranchIterator begin();
  BranchEndIterator end();

 private:
  // The git2 c-style branch iterator
  g3::unique_ptr<git_branch_iterator> g2_iterator_;
};

}  // namespace g3
