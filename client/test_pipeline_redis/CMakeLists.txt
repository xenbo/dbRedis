cmake_minimum_required(VERSION 3.10)
project(test_pipeline_redis)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
link_directories(/usr/local/lib64/)

add_executable(test_pipeline_redis main.cpp)
target_link_libraries(test_pipeline_redis hiredis pthread)
