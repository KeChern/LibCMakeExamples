cmake_minimum_required(VERSION 3.10)
project(EigenCrossExample)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 找到 Eigen3 库
find_package(Eigen3 REQUIRED)

# 添加可执行文件
add_executable(main main.cpp)

# 链接 Eigen
target_include_directories(main PRIVATE ${EIGEN3_INCLUDE_DIR})
