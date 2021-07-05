#pragma once

#include "git2.h"

#include "git3/branch.hh"
#include "git3/oid.hh"

#include "absl/container/flat_hash_map.h"

#include <unordered_map>
#include <vector>

namespace g3 {

class BranchTreeNode {
 public:
  friend class BranchTreeBuilder;

  BranchTreeNode(Branch b) noexcept : _branch(std::move(b)) {}

  BranchTreeNode(BranchTreeNode&&) noexcept = default;
  BranchTreeNode& operator=(BranchTreeNode&&) noexcept = default;

 private:
  Branch _branch;
  std::vector<BranchTreeNode> _downstreamBranches;
};

class BranchTree {
 public:
  BranchTree(BranchTreeNode root) noexcept : _root(std::move(root)) {}

 private:
  BranchTreeNode _root;
};

// This class represents a cycle of branches, a collection of branches
// where each branch's upstream is another branch in the cycle.
class BranchCycle {
 public:
  BranchCycle(std::vector<Branch>&& branches) noexcept
      : _branches(std::move(branches)) {}

 private:
  // Each branch's upstream is the following branch. The last
  // branch's upstream is the first branch
  std::vector<Branch> _branches;
};

class BranchTreeBuilder {
 public:
  BranchTreeBuilder() noexcept = default;

  // The internal state of the builder
  struct State {
    State() noexcept : _branches(), _edges() {}

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    State(State&&) noexcept = default;
    State& operator=(State&&) noexcept = default;

    absl::flat_hash_map<Oid, Branch> _branches;
    absl::flat_hash_map<Oid, std::vector<Oid>> _edges;
  };

  // Add a branch to the builder
  void addBranch(Branch&& b);

  // Produce the actual tree. Non-const since we will
  // move Branch objects out of the internal state
  BranchTree buildTree();

  // Build a branch tree object, moving branches from the State
  // object into the Tree.
  static BranchTree buildTree(State&&);

  // Build a branch cycle object, moving branches from the State
  // object into the Cycle.
  static BranchCycle buildCycle(State&&);

 private:
  State _state;
};

// Cycle Detected is thrown when git3 detects that the graph of branches
// is _not_ a DAG (because it's not acyclical). Surprisingly git actually
// is fine with creating a branch structure that looks like this, so it's
// a condition that we need to handle.
//
// This exception class will contain a list of all of the upstream links
// that participate in the cycle, sorted into the cycle order, for example,
// A->X, X->B, B->A (note that this is different than alphabetic order).
class CycleDetected : public std::exception {
 public:
  friend class BranchTreeBuilder;

  const char* what() const noexcept override { return "Cycle Detected"; }

 private:
  // Cycle Detected is _only_ thrown by BranchTreeBuilder, and the builder's
  // state is moved into the exception.
  CycleDetected(BranchTreeBuilder::State&& state) : _state(std::move(state)) {}

  // The state of the builder at the time that the cycle was detected. This
  // should contain _only_ the branches that are participants in the cycle.
  BranchTreeBuilder::State _state;
};

// No Branches is thrown when git3 detects that the current repository does not
// contain _any_ branches. One way that this can happen is in a completely fresh
// git repo, where `git init` has been run, but nothing else has.
class NoBranches : public std::exception {
  const char* what() const noexcept override { return "No Branches"; }
};

}  // namespace g3
