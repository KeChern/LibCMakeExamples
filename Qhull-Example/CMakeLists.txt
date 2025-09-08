cmake_minimum_required(VERSION 3.10)
project(QhullExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Homebrew 的默认路径（防止 M1/M2 找不到）
set(HOMEBREW_PREFIX "/opt/homebrew")

# 添加 include 和 lib 路径
include_directories("/opt/homebrew/include")
link_directories("/opt/homebrew/lib")

find_package(Eigen3 REQUIRED)

# 构建可执行文件
add_executable(3DConvexHull 3DConvexHull.cpp)
add_executable(4DConvexHull 4DConvexHull.cpp)
add_executable(dDComputeMinDistance dDComputeMinDistance.cpp)

# 链接 Qhull 库
target_link_libraries(3DConvexHull qhullcpp qhull_r)
target_link_libraries(4DConvexHull qhullcpp qhull_r)
target_link_libraries(dDComputeMinDistance qhullcpp qhull_r)

target_include_directories(dDComputeMinDistance PRIVATE ${EIGEN3_INCLUDE_DIR})