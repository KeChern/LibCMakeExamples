cmake_minimum_required(VERSION 3.10)
project(Eigen_AutoDiff)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

find_package(Eigen3 REQUIRED)
add_executable(main main.cpp)
target_include_directories(main PRIVATE ${EIGEN3_INCLUDE_DIRS})
