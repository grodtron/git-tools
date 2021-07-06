#include <filesystem>
#include "gtest/gtest.h"

#include "git2.h"

#include "git3/branch_tree.hh"
#include "git3/repo.hh"

#include "git3/testing/git_fixture.hh"

#include "fmt/core.h"
#include "stdx/cstdlib.hh"

class BranchTreeBuilder : public g3::GitRepoFixture {};

TEST_F(BranchTreeBuilder, empty_repository) {
  g3::BranchTreeBuilder sut;

  for (auto b : repo().branches()) {
    sut.addBranch(std::move(b));
  }

  ASSERT_THROW(sut.buildTree(), g3::NoBranches);
}

TEST_F(BranchTreeBuilder, one_commit_no_branch) {
  g3::BranchTreeBuilder sut;

  initial_commit();

  for (auto b : repo().branches()) {
    sut.addBranch(std::move(b));
  }

  const auto tree = sut.buildTree();

  ASSERT_EQ(tree.root()->name(), "master");
  ASSERT_EQ(tree.root().children().size(), 0);
}

TEST_F(BranchTreeBuilder, two_branches) {
  g3::BranchTreeBuilder sut;

  initial_commit();
  add_branch("A");
  set_upstream("A", "master");
  add_branch("B");
  set_upstream("B", "A");

  for (auto b : repo().branches()) {
    sut.addBranch(std::move(b));
  }

  const auto tree = sut.buildTree();

  ASSERT_EQ(tree.root()->name(), "master");
  ASSERT_EQ(tree.root().children().size(), 1);

  const auto& firstChild = *tree.root().children().begin();

  ASSERT_EQ(firstChild->name(), "A");
  ASSERT_EQ(firstChild.children().size(), 1);

  const auto& grandChild = *firstChild.children().begin();

  ASSERT_EQ(grandChild->name(), "B");
  ASSERT_EQ(grandChild.children().size(), 0);
}

TEST_F(BranchTreeBuilder, cycle) {
  g3::BranchTreeBuilder sut;

  initial_commit();
  add_branch("C");
  add_branch("A");
  add_branch("B");
  set_upstream("C", "B");
  set_upstream("B", "A");
  set_upstream("A", "C");

  for (auto b : repo().branches()) {
    sut.addBranch(std::move(b));
  }

  try {
    sut.buildTree();
    FAIL() << "g3::CycleDetected should be thrown";
  } catch (g3::CycleDetected& e) {
    const auto cycle = g3::BranchTreeBuilder::buildCycle(std::move(e));

    const auto& branches = cycle.branches();
    ASSERT_EQ(branches.size(), 3);
    ASSERT_EQ(branches[0].name(), "A");
    ASSERT_EQ(branches[1].name(), "B");
    ASSERT_EQ(branches[2].name(), "C");
  }
}
