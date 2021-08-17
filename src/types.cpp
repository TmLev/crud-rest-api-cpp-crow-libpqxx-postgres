#include <crow/json.h>
#include <tl/expected.hpp>

#include "types.hpp"

////////////////////////////////////////////////////////////////////////////////
// Error

auto Error::New(String details) -> tl::unexpected<Error> {
  return tl::make_unexpected(Error{
      .details = std::move(details),
  });
}

auto Error::IntoJson() const -> crow::json::wvalue {
  auto json = crow::json::wvalue();
  json["details"] = details;
  return json;
}
