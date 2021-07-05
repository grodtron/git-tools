#pragma once

#include <filesystem>
#include "gtest/gtest.h"

#include "git3/repo.hh"

namespace g3 {

class GitRepoFixture : public ::testing::Test {
 public:
  void SetUp() override;

 protected:
  std::filesystem::path root_directory() const;

  g3::Repo& repo();

  void initial_commit();
  void add_branch(std::string branch);
  void set_upstream(std::string branch, std::string upstream);

 private:
  void commit(std::string token);

  std::filesystem::path root_;
  g3::Repo repo_;
};

}  // namespace g3
