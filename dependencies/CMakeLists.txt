# ------------------------------------------------------------------------------
# Threads

find_package(Threads)
set(THREADS_LINK_TARGET ${CMAKE_THREAD_LIBS_INIT} PARENT_SCOPE)

# ------------------------------------------------------------------------------
# Crow

find_package(ZLIB)

find_package(
  Boost 1.70
  COMPONENTS system thread
  REQUIRED)
set(BOOST_INCLUDE_DIRECTORY
    ${Boost_INCLUDE_DIR}
    PARENT_SCOPE)

set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
add_subdirectory(crow)

set(CROW_INCLUDE_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/crow/include"
    PARENT_SCOPE)

# ------------------------------------------------------------------------------
# libpqxx

set(BUILD_DOC OFF)
set(BUILD_TEST OFF)
add_subdirectory(libpqxx)

set(LIBPQXX_INCLUDE_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/libpqxx/include"
    PARENT_SCOPE)

# ------------------------------------------------------------------------------
# expected

set(EXPECTED_BUILD_TESTS OFF)
set(EXPECTED_BUILD_PACKAGE OFF)
add_subdirectory(expected)
