cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -fopenmp")

project(worldengine VERSION 0.1)

include_directories(
    worldengine
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/testing
)

file(
    GLOB
    worldengine_SRC
    "./src/*.cpp"
    "*.cpp"
    "*.hpp"
    "*.h"
    "*.c"
)

# boost ------------------------------------------------------------------
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.50 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

# wxWidgets --------------------------------------------------------------
find_package(
    wxWidgets 
    COMPONENTS
    core base
    REQUIRED
)

include(${wxWidgets_USE_FILE})

add_executable(
    worldengine
    ${worldengine_SRC}
)

target_precompile_headers(
    worldengine
    PUBLIC
    pch.h
)

if (UNIX) #--------------------------------------------------------------
# LINUX
#------------------------------------------------------------------------
target_link_libraries(
    worldengine
    SDL2
    SDL2main
    SDL2_image
    SDL2_ttf
    SDL2_net
    sqlite3
    gtest
    gmock
    GLEW
    GL
    ${wxWidgets_LIBRARIES}
    Boost::filesystem
)
endif()
