cmake_minimum_required(VERSION 3.12)
project(CppADExample)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 检测 Homebrew 安装路径
execute_process(
        COMMAND brew --prefix
        OUTPUT_VARIABLE HOMEBREW_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
)

# 如果找到 Homebrew，设置搜索路径
if(HOMEBREW_PREFIX)
    message(STATUS "Found Homebrew at: ${HOMEBREW_PREFIX}")
    set(CMAKE_PREFIX_PATH ${HOMEBREW_PREFIX} ${CMAKE_PREFIX_PATH})

    # 设置 CppAD 的具体路径
    set(CPPAD_INCLUDE_DIR "${HOMEBREW_PREFIX}/include")
    set(CPPAD_LIBRARY_DIR "${HOMEBREW_PREFIX}/lib")

    message(STATUS "CppAD include directory: ${CPPAD_INCLUDE_DIR}")
    message(STATUS "CppAD library directory: ${CPPAD_LIBRARY_DIR}")
endif()

# 查找 CppAD 库文件
find_library(CPPAD_LIB
        NAMES cppad_lib
        PATHS ${CPPAD_LIBRARY_DIR}
        NO_DEFAULT_PATH)

# 找到 Eigen3 库
find_package(Eigen3 REQUIRED)

# 创建可执行文件
add_executable(cppAD_example main.cpp)

# 添加头文件搜索路径
target_include_directories(cppAD_example PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(cppAD_example PRIVATE ${CPPAD_INCLUDE_DIR})

target_link_libraries(cppAD_example ${CPPAD_LIB})

