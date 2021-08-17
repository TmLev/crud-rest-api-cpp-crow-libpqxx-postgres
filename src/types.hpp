#ifndef REST_API_TYPES
#define REST_API_TYPES

#include <tl/expected.hpp>
#include <crow/json.h>

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

inline constexpr auto None = std::nullopt;  // NOLINT

using String = std::string;

template <typename T>
using Vec = std::vector<T>;

////////////////////////////////////////////////////////////////////////////////
// Errors

struct Error {
  String details;

  static auto New(String details) -> tl::unexpected<Error>;

  auto IntoJson() const -> crow::json::wvalue;
};

#endif  // REST_API_TYPES
