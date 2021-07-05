#include "git_fixture.hh"

#include <filesystem>
#include "fmt/core.h"
#include "stdx/cstdlib.hh"

namespace g3 {

void GitRepoFixture::SetUp() {
  const auto* const test_info =
      testing::UnitTest::GetInstance()->current_test_info();

  root_ = std::filesystem::path{std::getenv("TEST_UNDECLARED_OUTPUTS_DIR")} /
          test_info->test_suite_name() / test_info->name();

  std::filesystem::create_directories(root_);
  std::filesystem::current_path(root_);

  stdx::system("git init");
  stdx::system(fmt::format("git config user.name {}", test_info->name()));
  stdx::system(fmt::format("git config user.email {}@{}.test",
                           test_info->name(), test_info->test_suite_name()));

  repo_ = g3::Repo::open(root_);
}

void GitRepoFixture::commit(std::string token) {
  stdx::system(fmt::format("touch {}", token));
  stdx::system(fmt::format("git add {}", token));
  stdx::system(fmt::format("git commit -m '{}'", token));
}

void GitRepoFixture::initial_commit() { commit("initial-commit"); }

void GitRepoFixture::add_branch(std::string branch) {
  stdx::system(fmt::format("git checkout -b {}", branch));
  commit(branch);
}
void GitRepoFixture::set_upstream(std::string branch, std::string upstream) {
  stdx::system(fmt::format("git branch -u {} {}", upstream, branch));
}

std::filesystem::path GitRepoFixture::root_directory() const { return root_; }
g3::Repo& GitRepoFixture::repo() { return repo_; }
}  // namespace g3
