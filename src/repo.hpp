#ifndef REST_API_REPO
#define REST_API_REPO

#include <pqxx/pqxx>

#include "models.hpp"
#include "types.hpp"

class PgRepo {
 public:
  // Constructors

  static auto New() -> PgRepo;

  // Operations

  auto ListArtists() -> Result<Vec<Artist>, Error>;

  auto RetrieveArtist(i32 id) -> Result<Artist, Error>;

  auto CreateArtist(NewArtist new_artist) -> Result<Artist, Error>;

  auto UpdateArtist(i32 id, UpdatedArtist updated_artist)
      -> Result<Artist, Error>;

  auto DestroyArtist(i32 id) -> Result<Artist, Error>;

 private:
  PgRepo(pqxx::connection connection);

 private:
  pqxx::connection connection_;
};

#endif  // REST_API_REPO
