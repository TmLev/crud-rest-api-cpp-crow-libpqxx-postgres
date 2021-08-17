#ifndef REST_API_MODELS
#define REST_API_MODELS

#include <crow/json.h>

#include "types.hpp"

struct Artist {
  i32 id;
  String name;
  String description;

  auto IntoJson() const -> crow::json::wvalue;
};

struct NewArtist {
  String name;
  String description;

  static auto From(const crow::json::rvalue& json) -> NewArtist;
};

struct UpdatedArtist {
  Option<String> name;
  Option<String> description;

  static auto From(const crow::json::rvalue& json) -> UpdatedArtist;
};

#endif  // REST_API_MODELS
