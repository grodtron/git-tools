#pragma once

#include <string>

namespace stdx {
int system(std::string cmd);
int system(const char* const cmd);

}  // namespace stdx
