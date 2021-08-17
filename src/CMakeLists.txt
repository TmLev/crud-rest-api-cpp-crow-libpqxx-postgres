add_executable(
  rest-api
  main.cpp
  models.cpp
  repo.cpp
  types.cpp
  wheels.cpp)
enable_compiler_warnings(rest-api)

# Link dependencies.
target_link_libraries(
  rest-api
  PRIVATE expected
  PRIVATE pqxx)

# Include dependency directories.
target_include_directories(
  rest-api SYSTEM
  PRIVATE ${CROW_INCLUDE_DIRECTORY}
  PRIVATE ${BOOST_INCLUDE_DIRECTORY}
  PRIVATE ${LIBPQXX_INCLUDE_DIRECTORY})
