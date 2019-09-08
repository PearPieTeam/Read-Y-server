cmake_minimum_required(VERSION 3.5)
project(ServerBackend)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_INCLUDE_DIR "libs")
set(PISTACHE_INCLUDE_DIR "libs/pistache/include")
set(RAPIDJSON_INCLUDE_DIR "libs/pistache/third-party/rapidjson/include")
set(LIBPQXX_INCLUDE_DIR "libs/libpqxx/include")
set(LIBPQXX_HEADER_INCLUDE_DIR "/usr/include/postgresql")

set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR} ${LIBPQXX_INCLUDE_DIR} ${LIBPQXX_HEADER_INCLUDE_DIR})

set(EXTRA_LIBRARY "-pthread -lpq")
set(LIBRARIES_SEARCH_PATHS ${EXTRA_LIBRARY})

include_directories(${HEADER_SEARCH_PATHS})

file(GLOB PISTACHE_SRC "libs/pistache/src/common/*.cc" "libs/pistache/src/client/*.cc" "libs/pistache/src/server/*.cc")
file(GLOB LIBPQXX_SRC "libs/libpqxx/src/*.cxx")
file(GLOB UTILS_FILES "utils/*.h" "utils/*.cpp")

#find_package(pistache)

add_subdirectory("libs/pistache")
add_subdirectory("libs/libpqxx")
#add_subdirectory("libs/pistache/third-party/rapidjson")

add_executable(${PROJECT_NAME} src/main.cpp ${PISTACHE_SRC} ${LIBPQXX_SRC} ${UTILS_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})