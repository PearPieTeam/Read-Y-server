cmake_minimum_required(VERSION 3.5)
project(ServerBackend)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_INCLUDE_DIR "libs")
set(PISTACHE_INCLUDE_DIR "libs/pistache/include")
set(NLOHMANN_INCLUDE_DIR "libs/nlohmann")

set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR} ${NLOHMANN_INCLUDE_DIR})

#set(EXTRA_LIBRARY "-pthread -lssl")

set(EXTRA_LIBRARY "-pthread")
set(LIBRARIES_SEARCH_PATHS ${EXTRA_LIBRARY})

include_directories(${HEADER_SEARCH_PATHS})

file(GLOB PISTACHE_SRC "libs/pistache/src/common/*.cc" "libs/pistache/src/client/*.cc" "libs/pistache/src/server/*.cc")

add_executable(${PROJECT_NAME} src/main.cpp ${PISTACHE_SRC} utils/utils.cpp utils/utils.h)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})