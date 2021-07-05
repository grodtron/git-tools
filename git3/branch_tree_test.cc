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
}

TEST_F(BranchTreeBuilder, cycle) {
  g3::BranchTreeBuilder sut;

  initial_commit();
  add_branch("A");
  add_branch("B");
  add_branch("C");
  set_upstream("B", "A");
  set_upstream("C", "B");
  set_upstream("A", "C");

  for (auto b : repo().branches()) {
    sut.addBranch(std::move(b));
  }

  ASSERT_THROW(sut.buildTree(), g3::CycleDetected);
}
