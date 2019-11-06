cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(effective-cpp)
add_executable(out main.cc stock_factory.cc stock_factory.h type_switch.cc)
target_link_libraries(out pthread)
