cmake_minimum_required(VERSION 3.5)
project(ServerBackend)

set(CMAKE_CXX_STANDARD 17)

set(SKIP_BUILD_TEST OFF)

set(PISTACHE_INCLUDE_DIR "libs/pistache/include")
set(RAPIDJSON_INCLUDE_DIR "libs/pistache/third-party/rapidjson/include")
set(LIBPQXX_INCLUDE_DIR "libs/libpqxx/include")
set(LIBPQXX_HEADER_INCLUDE_DIR "/usr/include/postgresql")
set(LIBPQXX_HEADER_BUILD_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libs/libpqxx/include")
set(IXWEBSOCKET_INCLUDE_DIR "libs/IXWebSocket")

set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR} ${LIBPQXX_INCLUDE_DIR} ${LIBPQXX_HEADER_INCLUDE_DIR} ${LIBPQXX_HEADER_BUILD_INCLUDE_DIR})

set(EXTRA_LIBRARY "-pthread -lpq")
set(LIBRARIES_SEARCH_PATHS ${EXTRA_LIBRARY})

include_directories(${HEADER_SEARCH_PATHS})

file(GLOB PISTACHE_SRC "libs/pistache/src/common/*.cc" "libs/pistache/src/client/*.cc" "libs/pistache/src/server/*.cc")
file(GLOB LIBPQXX_SRC "libs/libpqxx/src/*.cxx")
file(GLOB UTILS_FILES "utils/chat_server/*.hpp" "utils/db_server/*.cpp" "utils/db_server/*.h" "utils/*.h" "utils/*.cpp")

add_subdirectory("libs/pistache")
add_subdirectory("libs/libpqxx")
add_subdirectory("libs/IXWebSocket")

link_libraries(ixwebsocket)

add_executable(${PROJECT_NAME} src/main.cpp ${PISTACHE_SRC} ${LIBPQXX_SRC} ${UTILS_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})