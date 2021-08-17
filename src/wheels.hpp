#ifndef REST_API_WHEELS
#define REST_API_WHEELS

#include "types.hpp"

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
// Macros

#define UNREACHABLE std::abort

////////////////////////////////////////////////////////////////////////////////
// Functions

auto Join(const Vec<String>& vec, const char* delim) -> String;

#endif  // REST_API_WHEELS
