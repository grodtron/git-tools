#pragma once

namespace g3 {
namespace internal {

// libgit2 requires static initialization of the library, but allows for the
// initialization to be done multiple times, as long as there are a
// corresponding number of shutdown calls. This simple RAII class manages
// matching those init and shutdown calls.
class Libgit2Initializer {
 public:
  Libgit2Initializer();
  ~Libgit2Initializer();
};

}  // namespace internal
}  // namespace g3
