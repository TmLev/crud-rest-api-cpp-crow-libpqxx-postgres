# CRUD REST API [C++ + Crow + libpqxx + Postgres]

API should allow simple CRUD operations over `artists` entities.

Current status:
- [x] List
- [x] Retrieve
- [x] Create
- [x] Update
- [x] Destroy

TODO:
- [ ] Run migrations automatically.
- [ ] Make `PgRepo` thread-safe (right now it is **NOT**).
- [x] Bump `libpqxx` when https://github.com/jtv/libpqxx/pull/476 will be merged.
- [x] Compile & run in Docker.
