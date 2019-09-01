CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(server)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(server main.cpp)

target_link_libraries(server LINK_PUBLIC z ssl uv uWS -lboost_regex)
