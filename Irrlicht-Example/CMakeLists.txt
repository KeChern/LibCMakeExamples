cmake_minimum_required(VERSION 3.10)
project(IrrlichtDemo)

set(CMAKE_CXX_STANDARD 17)

find_path(IRRLICHT_INCLUDE_DIR
        NAMES irrlicht.h
        PATHS /opt/homebrew/include /usr/local/include
        PATH_SUFFIXES irrlicht
)

find_library(IRRLICHT_LIBRARY
        NAMES Irrlicht
        PATHS /opt/homebrew/lib /usr/local/lib
)

# 输出找到的路径
message(STATUS "IRRLICHT_INCLUDE_DIR = ${IRRLICHT_INCLUDE_DIR}")
message(STATUS "IRRLICHT_LIBRARY = ${IRRLICHT_LIBRARY}")

if (NOT IRRLICHT_INCLUDE_DIR OR NOT IRRLICHT_LIBRARY)
    message(FATAL_ERROR "Could not find Irrlicht. Please make sure it is installed via Homebrew.")
endif()

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${IRRLICHT_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${IRRLICHT_LIBRARY})
