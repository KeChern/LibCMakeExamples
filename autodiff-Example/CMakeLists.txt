cmake_minimum_required(VERSION 3.10)
project(AutoDiffTest)

# 添加 autodiff 头文件
find_package(autodiff REQUIRED)
if(autodiff_FOUND)
    message(STATUS "Package autodiff was found.")
    message(STATUS "FILE: ${autodiff_DIRS}")
endif()

# 添加 Eigen 头文件
find_package(Eigen3 REQUIRED)

# 生成可执行文件
add_executable(ForwardMode main.cpp)
add_executable(ReverseMode main_reverse.cpp)

# 链接 autodiff 和 Eigen
target_include_directories(ForwardMode PUBLIC ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(ForwardMode autodiff::autodiff)

target_include_directories(ReverseMode PUBLIC ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(ReverseMode autodiff::autodiff)
