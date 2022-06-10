cmake_minimum_required(VERSION 3.9)
project(dbRedis)

#Redis 4.0.6
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DUSE_JEMALLOC=yes)
set(CMAKE_C_FLAGS "-std=gnu99 -Wall -pipe -g3 -O3 -funroll-loops ")


link_directories(/usr/local/lib)

include_directories(deps/jemalloc/include)
include_directories(deps/linenoise)
include_directories(deps/hiredis)
include_directories(deps/lua/src)
include_directories(src)

AUX_SOURCE_DIRECTORY(deps/hiredis SRChiredis)
AUX_SOURCE_DIRECTORY(deps/linenoise SRClinenois)
AUX_SOURCE_DIRECTORY(deps/lua/src SRClua)
AUX_SOURCE_DIRECTORY(src SRC)


add_library(hiredis ${SRChiredis})
add_library(linenoise ${SRClinenois})
add_library(lua ${SRClua})

include_directories(crypto_key)
add_executable(dbRedis ${SRC} crypto_key/cc_x25519.cpp crypto_key/x25519.cpp)
target_link_libraries(dbRedis hiredis jemalloc linenoise  lua dl  pthread rt m  cryptopp stdc++fs )

