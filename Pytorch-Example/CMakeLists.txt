cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(example-app)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(example-app main.cpp)
target_link_libraries(example-app "${TORCH_LIBRARIES}")
set_property(TARGET example-app PROPERTY CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
target_include_directories(example-app PRIVATE ${EIGEN3_INCLUDE_DIRS})

# 输出调试信息
message(STATUS "Found LibTorch: ${Torch_FOUND}")
message(STATUS "LibTorch version: ${Torch_VERSION}")
message(STATUS "LibTorch include directories: ${TORCH_INCLUDE_DIRS}")
message(STATUS "LibTorch libraries: ${TORCH_LIBRARIES}")


