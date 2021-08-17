#include <crow/json.h>

#include "models.hpp"
#include "types.hpp"

////////////////////////////////////////////////////////////////////////////////
// Internal

auto LoadString(const crow::json::rvalue& json, const char* key)
    -> Option<String> {
  if (json.has(key)) {
    return String{json[key].s()};
  } else {
    return None;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Artist

auto Artist::IntoJson() const -> crow::json::wvalue {
  auto json = crow::json::wvalue{};
  json["id"] = id;
  json["name"] = name;
  json["description"] = description;
  return json;
}

////////////////////////////////////////////////////////////////////////////////
// NewArtist

auto NewArtist::From(const crow::json::rvalue& json) -> NewArtist {
  return NewArtist{
    .name = LoadString(json, "name").value(),
    .description = LoadString(json, "description").value(),
  };
}

////////////////////////////////////////////////////////////////////////////////
// UpdatedArtist

auto UpdatedArtist::From(const crow::json::rvalue& json) -> UpdatedArtist {
  return UpdatedArtist{
      .name = LoadString(json, "name"),
      .description = LoadString(json, "description"),
  };
}
