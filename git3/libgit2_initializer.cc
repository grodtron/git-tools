
#include "git2.h"

#include "git3/libgit2_initializer.hh"

namespace g3 {
namespace internal {

Libgit2Initializer::Libgit2Initializer() { git_libgit2_init(); }
Libgit2Initializer::~Libgit2Initializer() { git_libgit2_shutdown(); }

}  // namespace internal
}  // namespace g3
