#include "stdx/cstdlib.hh"

#include <cstdlib>
#include <string>

namespace stdx {
int system(std::string cmd) { return std::system(cmd.c_str()); }
int system(const char* const cmd) { return std::system(cmd); }

}  // namespace stdx
