#ifndef REST_API_TYPES
#define REST_API_TYPES

#include <tl/expected.hpp>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Numeric

using u8 = std::uint8_t;    // NOLINT
using u16 = std::uint16_t;  // NOLINT
using u32 = std::uint32_t;  // NOLINT
using u64 = std::uint64_t;  // NOLINT

using i8 = std::int8_t;    // NOLINT
using i16 = std::int16_t;  // NOLINT
using i32 = std::int32_t;  // NOLINT
using i64 = std::int64_t;  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// Containers

template <typename T, typename E>
using Result = tl::expected<T, E>;

template <typename T>
using Option = std::optional<T>;

using String = std::string;

template <typename T>
using Vec = std::vector<T>;

////////////////////////////////////////////////////////////////////////////////
// Errors

struct Error {
  String details;
};

////////////////////////////////////////////////////////////////////////////////
// Utility

// Replacement for `void`.
struct Unit {};

#endif  // REST_API_TYPES
