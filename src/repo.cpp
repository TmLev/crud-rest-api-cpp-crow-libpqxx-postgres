#include <pqxx/pqxx>

#include "models.hpp"
#include "repo.hpp"
#include "wheels.hpp"

#include <cstdlib>

// Constructors

auto PgRepo::New() -> PgRepo {
  const auto host = String{std::getenv("POSTGRES_HOST")};
  const auto port = String{std::getenv("POSTGRES_PORT")};
  const auto db = String{std::getenv("POSTGRES_DB")};
  const auto user = String{std::getenv("POSTGRES_USER")};
  const auto password = String{std::getenv("POSTGRES_PASSWORD")};

  const auto url = "postgres://" + user + ":" + password + "@" + host + ":" +
                   port + "/" + db;

  return PgRepo(pqxx::connection{url});
}

PgRepo::PgRepo(pqxx::connection connection)
    : connection_{std::move(connection)} {
}

// Operations

auto PgRepo::ListArtists() -> Result<Vec<Artist>, Error> {
  try {
    auto txn = pqxx::work{connection_};
    const auto rows = txn.exec("SELECT * FROM artists");
    txn.commit();

    auto actors = Vec<Artist>{};
    actors.reserve(static_cast<u64>(rows.size()));

    for (const auto& row : rows) {
      const auto [id, name, description] = row.as<i32, String, String>();
      actors.push_back(Artist{
          .id = id,
          .name = std::move(name),
          .description = std::move(description),
      });
    }

    return actors;

  } catch (const std::exception& e) {
    return Error::New(e.what());
  }
}

auto PgRepo::RetrieveArtist(i32 id) -> Result<Artist, Error> {
  try {
    auto txn = pqxx::work{connection_};
    const auto row = txn.exec1(
        "SELECT * FROM artists "
        "WHERE id = " +
        pqxx::to_string(id));
    txn.commit();

    const auto [_, name, description] = row.as<i32, String, String>();
    return Artist{
        .id = id,
        .name = name,
        .description = description,
    };
  } catch (const std::exception& e) {
    return Error::New(e.what());
  }
}

auto PgRepo::CreateArtist(NewArtist new_artist) -> Result<Artist, Error> {
  try {
    auto txn = pqxx::work{connection_};
    const auto values =
        txn.quote(new_artist.name) + ", " + txn.quote(new_artist.description);
    const auto row = txn.exec1(
        "INSERT INTO artists(name, description) "
        "VALUES (" +
        values +
        ") "
        "RETURNING *");
    txn.commit();

    const auto [id, name, description] = row.as<i32, String, String>();
    return Artist{
        .id = id,
        .name = name,
        .description = description,
    };
  } catch (const std::exception& e) {
    return Error::New(e.what());
  }
}

auto PgRepo::UpdateArtist(i32 id, UpdatedArtist updated_artist)
    -> Result<Artist, Error> {
  try {
    auto txn = pqxx::work{connection_};

    auto sets = Vec<String>{};
    auto add_set = [&](String column, const Option<String>& updated) {
      if (updated.has_value()) {
        sets.push_back(column + " = " + txn.quote(updated.value()));
      }
    };
    add_set("name", updated_artist.name);
    add_set("description", updated_artist.description);

    const auto row = txn.exec1(
        "UPDATE artists "
        "SET " +
        Join(sets, ", ") +
        " "
        "WHERE id = " +
        pqxx::to_string(id) +
        " "
        "RETURNING *");
    txn.commit();

    const auto [_, name, description] = row.as<i32, String, String>();
    return Artist{
        .id = id,
        .name = name,
        .description = description,
    };
  } catch (const std::exception& e) {
    return Error::New(e.what());
  }
}

auto PgRepo::DestroyArtist(i32 id) -> Result<Artist, Error> {
  try {
    auto txn = pqxx::work{connection_};
    const auto row = txn.exec1(
        "DELETE FROM artists "
        "WHERE id = " +
        pqxx::to_string(id) + "RETURNING *");
    txn.commit();

    const auto [_, name, description] = row.as<i32, String, String>();
    return Artist{
        .id = id,
        .name = name,
        .description = description,
    };
  } catch (const std::exception& e) {
    return Error::New(e.what());
  }
}
