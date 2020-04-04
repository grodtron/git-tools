#include "git3/repo.hh"
#include "git3/pointer_types.hh"

#include <exception>
#include <string>

namespace g3 {

Repo Repo::open(std::string path) {
  git_repository* repo = nullptr;

  if (!git_repository_open(&repo, path.c_str())) {
    return Repo(repo);
  } else {
    const auto error = git_error_last();
    throw std::runtime_error(error->message);
  }
}

BranchRange Repo::branches() const {
  git_branch_iterator* it = nullptr;
  git_branch_iterator_new(&it, repo_.get(), GIT_BRANCH_LOCAL);

  // TODO error handling
  return BranchRange(it);
}

}  // namespace g3
