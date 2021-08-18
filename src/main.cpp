#define CROW_MAIN

#include <crow/app.h>
#include <crow/json.h>
#include <crow/routing.h>

#include "repo.hpp"
#include "types.hpp"
#include "wheels.hpp"

#include <cstdlib>   // std::getenv
#include <signal.h>  // signal
#include <string>    // std::stoi

auto GetPortFromEnv() -> u16 {
  const auto raw = String{std::getenv("REST_API_PORT")};
  assert(raw.size() >= 4);  // At least greater than 1000.
  return static_cast<u16>(std::stoi(raw));
}

auto main() -> int {
  // Initialize Postgres repo.

  // Broken Postgres connection leads to `SIGPIPE`.
  // Default action in such case is to abort, change it to ignore.
  signal(SIGPIPE, SIG_IGN);

  auto repo = PgRepo::New();

  // Create web application.

  auto app = crow::SimpleApp{};

  // Register routes.

  CROW_ROUTE(app, "/artists/")
      .methods(crow::HTTPMethod::GET,
               crow::HTTPMethod::POST)([&](const crow::request& request) {
        switch (request.method) {
          case crow::HTTPMethod::GET: {
            const auto result = repo.ListArtists();
            if (!result.has_value()) {
              return result.error().IntoJson();
            }

            const auto artists = std::move(result.value());

            auto serialized = Vec<crow::json::wvalue>{};
            serialized.reserve(artists.size());
            for (const auto& artist : artists) {
              serialized.push_back(artist.IntoJson());
            }

            return crow::json::wvalue(serialized);
          }

          case crow::HTTPMethod::POST: {
            const auto json = crow::json::load(request.body);
            const auto result = repo.CreateArtist(NewArtist::From(json));
            if (!result.has_value()) {
              return result.error().IntoJson();
            }

            const auto artist = std::move(result.value());

            return artist.IntoJson();
          }

          default: {
            UNREACHABLE();
          }
        }
      });

  CROW_ROUTE(app, "/artists/<int>/")
      .methods(
          crow::HTTPMethod::GET, crow::HTTPMethod::PATCH,
          crow::HTTPMethod::DELETE)([&](const crow::request& request, int id) {
        switch (request.method) {
          case crow::HTTPMethod::GET: {
            const auto result = repo.RetrieveArtist(id);
            if (!result.has_value()) {
              return result.error().IntoJson();
            }

            const auto artist = result.value();

            return artist.IntoJson();
          }

          case crow::HTTPMethod::PATCH: {
            const auto json = crow::json::load(request.body);
            const auto result =
                repo.UpdateArtist(id, UpdatedArtist::From(json));
            if (!result.has_value()) {
              return result.error().IntoJson();
            }

            const auto artist = result.value();

            return artist.IntoJson();
          }

          case crow::HTTPMethod::DELETE: {
            const auto result = repo.DestroyArtist(id);
            if (!result.has_value()) {
              return result.error().IntoJson();
            }

            const auto artist = result.value();

            return artist.IntoJson();
          }

          default: {
            UNREACHABLE();
          }
        }
      });

  // Run.

  app.port(GetPortFromEnv()).run();

  // Exit.

  return EXIT_SUCCESS;
}
