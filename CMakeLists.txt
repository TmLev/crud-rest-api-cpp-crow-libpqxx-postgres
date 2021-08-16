cmake_minimum_required(VERSION 3.18)

project(
  rest-api
  VERSION 0.1.0
  DESCRIPTION "Simple REST API"
  LANGUAGES CXX)

# Import CMake utils.
include(cmake/Ccache.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/ProjectSettings.cmake)
include(cmake/StaticAnalyzers.cmake)

# Include dependencies.
add_subdirectory(dependencies)

# Debug include directories for dependencies.
message(STATUS "crow include = ${CROW_INCLUDE_DIRECTORY}")
message(STATUS "libpqxx include = ${LIBPQXX_INCLUDE_DIRECTORY}")

# Main target lives in `src`.
add_subdirectory(src)
