cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -fopenmp")

add_definitions("-DBOOST_ALL_NO_LIB")

project(worldengine VERSION 0.1)

# UNIX ///////////////////////////////////////////////////////////////////////
if(UNIX)
    # boost ------------------------------------------------------------------
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        set(build_dir ${CMAKE_SOURCE_DIR}/build/linux_x64/Debug/)
    else()
        set(build_dir ${CMAKE_SOURCE_DIR}/build/linux_x64/Release/)
    endif()

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
endif()


# WIN32 ////////////////////////////////////////////////////////////////////
if (WIN32)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        set(build_dir ${CMAKE_SOURCE_DIR}/build/win_x64/Debug/)
    else()
        set(build_dir ${CMAKE_SOURCE_DIR}/build/win_x64/Release/)
    endif()

    set(Boost_INCLUDE_DIR "C:/local/boost_1_75_0/")

    find_package(Boost 1.75 REQUIRED)
    if(Boost_FOUND)
        # boost ------------------------------------------------------------------
        set(Boost_USE_STATIC_LIBS        OFF)  # only find static libs
        set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
        set(Boost_USE_RELEASE_LIBS       OFF)  # only find release libs
        set(Boost_USE_MULTITHREADED      OFF)
        set(Boost_USE_STATIC_RUNTIME    OFF)

        message(STATUS "Boost version: ${Boost_VERSION}")

        include_directories(${Boost_INCLUDE_DIRS})
    else()
        message("Boost not found...")
    endif()


    # wxWidgets --------------------------------------------------------------
    find_package(
        wxWidgets 
        COMPONENTS
        core base
        REQUIRED
    )
    include(${wxWidgets_USE_FILE})
endif()

# XPLATFORM ////////////////////////////////////////////////////////////////
set(CMAKE_BUILD_DIR ${build_dir})
set(EXECUTABLE_OUTPUT_PATH ${build_dir})

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


add_executable(
    worldengine
    ${worldengine_SRC}
)

target_precompile_headers(
    worldengine
    PUBLIC
    pch.h
)

# LIBARIES LINKING ///////////////////////////////////////////////////////////
if (WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    target_compile_options(worldengine PUBLIC /MT)
    target_link_options(worldengine PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)

    target_link_directories(
        worldengine
        PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/Release
    )

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_link_libraries(
        worldengine
        SDL2.lib
        SDL2main.lib
        SDL2_image.lib
        SDL2_ttf.lib
        SDL2test.lib
        opengl32.lib 
        glew32d.lib
        ${wxWidgets_LIBRARIES}
    )
    else()
        target_link_libraries(
        worldengine
        SDL2.lib
        SDL2main.lib
        SDL2_image.lib
        SDL2_ttf.lib
        SDL2test.lib
        opengl32.lib 
        glew32.lib
        ${wxWidgets_LIBRARIES}
    )
    endif()
endif()

if (UNIX)
    # Build static
    #set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    #set(BUILD_SHARED_LIBS OFF)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    
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
    )
endif()
