#pragma once

#include "git3/branch.hh"

#include "git2.h"

#include <memory>
#include <optional>

namespace g3 {

class BranchEndIterator {};

class BranchIterator {
 public:
  BranchIterator(std::unique_ptr<git_branch_iterator,
                                 decltype(&git_branch_iterator_free)>);

  BranchIterator& operator++();

  Branch operator*();

  bool operator!=(const BranchEndIterator& other) {
    // If the iterator has a current branch, then it's not equal to the end
    // iterator
    return static_cast<bool>(current_branch_);
  }

 private:
  void next_();

  std::optional<Branch> current_branch_;

  // The git2 c-style branch iterator
  std::unique_ptr<git_branch_iterator, decltype(&git_branch_iterator_free)>
      g2_iterator_;

  // friend class BranchEndIterator;
};

class BranchRange {
 public:
  BranchRange(git_branch_iterator*);

  BranchIterator begin();
  BranchEndIterator end();

 private:
  // The git2 c-style branch iterator
  std::unique_ptr<git_branch_iterator, decltype(&git_branch_iterator_free)>
      g2_iterator_;
};

}  // namespace g3
