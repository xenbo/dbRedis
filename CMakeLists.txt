cmake_minimum_required(VERSION 3.9)
project(dbRedis C)

#Redis 4.0.6
set(CMAKE_C_STANDARD 99)


include_directories(deps/hiredis)
include_directories(deps/linenoise)
include_directories(deps/lua/src)
include_directories(src)


AUX_SOURCE_DIRECTORY(deps/hiredis SRChiredis)
AUX_SOURCE_DIRECTORY(deps/linenoise SRClinenois)
AUX_SOURCE_DIRECTORY(deps/lua/src SRClua)
AUX_SOURCE_DIRECTORY(src SRC)


add_library(hiredis ${SRChiredis})
add_library(linenoise ${SRClinenois})
add_library(lua ${SRClua})


add_executable(dbRedis ${SRC})
target_link_libraries(dbRedis hiredis linenoise lua dl  pthread rt m)

