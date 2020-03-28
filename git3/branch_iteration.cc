#include "git3/branch_iteration.hh"
#include "git3/branch.hh"

#include "git2.h"

#include <memory>

namespace g3 {

BranchIterator::BranchIterator(
    std::unique_ptr<git_branch_iterator, decltype(&git_branch_iterator_free)>
        it)
    : g2_iterator_(std::move(it)) {
  // We start the iterator in basically a "before the beginning" state
  next_();
}

void BranchIterator::next_() {
  // We need to get the first value immediately
  // this whole thing is a little bit of a hack
  git_reference* branch = nullptr;
  git_branch_t branch_type;
  auto result = git_branch_next(&branch, &branch_type, g2_iterator_.get());

  if (result) {
    current_branch_ = std::nullopt;
  } else {
    current_branch_ = Branch(branch);
  }
}

BranchIterator& BranchIterator::operator++() {
  next_();
  return *this;
}

Branch BranchIterator::operator*() { return std::move(*current_branch_); }

BranchRange::BranchRange(git_branch_iterator* it)
    : g2_iterator_(it, git_branch_iterator_free) {}

BranchIterator BranchRange::begin() {
  return BranchIterator{std::move(g2_iterator_)};
}

BranchEndIterator BranchRange::end() { return BranchEndIterator{}; }

}  // namespace g3
