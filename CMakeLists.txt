cmake_minimum_required(VERSION 2.6.0)

option(BUILD_LIBSLMP "Build libslmp" ON)
option(BUILD_LIBMELCLI "Build libmelcli (MELSEC SLMP Client Library)" ON)
option(BUILD_SAMPLES "Build samples" ON)
# Build shared (.dll/.so) when ON, static (.lib/.a) when OFF.
# Pass -DBUILD_SHARED_LIBS=OFF to produce static libraries.
option(BUILD_SHARED_LIBS "Build shared libraries (OFF to build static libraries)" ON)

project(libslmp2)

if (BUILD_LIBSLMP)
    add_subdirectory(${PROJECT_SOURCE_DIR}/libslmp)
endif ()

if (BUILD_LIBMELCLI)
    add_subdirectory(${PROJECT_SOURCE_DIR}/libmelcli)
endif ()

if (BUILD_SAMPLES)
    add_subdirectory(${PROJECT_SOURCE_DIR}/samples)
endif ()
