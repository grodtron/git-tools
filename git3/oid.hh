#pragma once

#include "git2.h"

namespace g3 {

// This class wraps a raw pointer to a libgit2 OID, but
// does not own it.
class Oid {
 public:
  Oid(const git_oid* o) noexcept : _oid(*o) {}

  template <typename T>
  friend class std::hash;

  template <typename H>
  friend H AbslHashValue(H h, const Oid& o) {
    return H::combine(std::move(h),
                      *reinterpret_cast<const uint32_t*>(o._oid.id));
  }

  bool operator==(const Oid& o) const { return git_oid_equal(&_oid, &o._oid); }
  bool operator!=(const Oid& o) const { return !(*this == o); }

 private:
  git_oid _oid;
};
}  // namespace g3

namespace std {
template <>
struct hash<g3::Oid> {
  int32_t operator()(const g3::Oid& o) const {
    return *reinterpret_cast<const int32_t*>(o._oid.id);
  }
};
}  // namespace std
