cmake_minimum_required(VERSION 3.5)

project(learnZeromq C CXX)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(cppzmq)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(cppzmq)

add_executable(hwserver hwserver.cpp)
add_executable(hwclient hwclient.cpp)
add_executable(wuserver wuserver.cpp)


