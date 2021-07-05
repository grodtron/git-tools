#pragma once

#include <memory>
#include "git2.h"

namespace g3 {

namespace internal {

template <typename T>
std::nullptr_t deleter = nullptr;

#define REGISTER_DELETER(Type, DeleterFn) \
  template <>                             \
  inline decltype(&DeleterFn) deleter<Type> = DeleterFn;

REGISTER_DELETER(git_branch_iterator, git_branch_iterator_free);
REGISTER_DELETER(git_repository, git_repository_free);
REGISTER_DELETER(git_reference, git_reference_free);

#undef REGISTER_DELETER

template <typename T>
using deleter_type = decltype(deleter<T>);

template <typename T>
using std_unique_ptr = std::unique_ptr<T, deleter_type<T>>;

}  // namespace internal

template <typename T>
class unique_ptr : public internal::std_unique_ptr<T> {
 public:
  unique_ptr(T* t) noexcept
      : internal::std_unique_ptr<T>(t, internal::deleter<T>) {}

  unique_ptr() noexcept
      : internal::std_unique_ptr<T>(nullptr, internal::deleter<T>) {}
  unique_ptr(std::nullptr_t) noexcept
      : internal::std_unique_ptr<T>(nullptr, internal::deleter<T>) {}

  unique_ptr(unique_ptr&& o) noexcept = default;
  unique_ptr& operator=(unique_ptr&&) = default;
  unique_ptr(unique_ptr& o) noexcept = delete;
};

}  // namespace g3
