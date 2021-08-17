#include "wheels.hpp"

auto Join(const Vec<String>& vec, const char* delim) -> String {
  auto res = std::stringstream{};

  auto first = true;
  for (const auto& elem : vec) {
    if (first) {
      first = false;
    } else {
      res << delim;
    }
    res << elem;
  }

  return res.str();
}
