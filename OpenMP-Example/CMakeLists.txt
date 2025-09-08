cmake_minimum_required(VERSION 3.10)
project(OpenMP-Example)

find_package(Eigen3 REQUIRED)

# Use OpenMP in the llvm in MacOS
set(CLANG_PATH "/opt/homebrew/opt/llvm/bin")

set(CMAKE_C_COMPILER "${CLANG_PATH}/clang")
set(CMAKE_CXX_COMPILER "${CLANG_PATH}/clang++")

set(OpenMP_C "${CMAKE_C_COMPILER}")
set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
set(OpenMP_C_LIB_NAMES "libomp")

set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
set(OpenMP_CXX_LIB_NAMES "libomp")

set(OpenMP_libomp_LIBRARY "libomp")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(openmp-example openmp-example.cpp)
add_executable(openmp-example2 openmp-example2.cpp)
target_include_directories(openmp-example2 PRIVATE ${EIGEN3_INCLUDE_DIR})


