cmake_minimum_required(VERSION 3.10)
project(NLoptExample)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 NLopt 库
find_package(NLopt REQUIRED)

# 添加可执行文件
add_executable(nlopt_example main.cpp)

# 链接 NLopt 库
target_link_libraries(nlopt_example NLopt::nlopt)