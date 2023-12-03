cmake_minimum_required(VERSION 2.6.0)

project(slmp)

include(GNUInstallDirs)

file (GLOB_RECURSE codec_sources ${PROJECT_SOURCE_DIR}/codec/*.c)
file (GLOB_RECURSE pktio_sources ${PROJECT_SOURCE_DIR}/packetio/*.c)
file (GLOB_RECURSE glthread_sources ${PROJECT_SOURCE_DIR}/glthread/*.c)
file (GLOB_RECURSE memory_sources ${PROJECT_SOURCE_DIR}/memory/*.c)
file (GLOB_RECURSE tsd_sources ${PROJECT_SOURCE_DIR}/tsd/*.c)
file (GLOB_RECURSE frameio_sources ${PROJECT_SOURCE_DIR}/frameio/*.c)
file (GLOB_RECURSE server_sources ${PROJECT_SOURCE_DIR}/server/*.c)

set(sources
    ${PROJECT_SOURCE_DIR}/libslmp.c
    ${PROJECT_SOURCE_DIR}/errmsg.c
    ${codec_sources}
    ${pktio_sources}
    ${glthread_sources}
    ${memory_sources}
    ${tsd_sources}
    ${frameio_sources}
    ${server_sources}
)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${PROJECT_SOURCE_DIR}/libslmp.def)
endif ()

add_library(slmp SHARED ${sources})

set_target_properties(slmp PROPERTIES
    PREFIX "lib"
    IMPORT_PREFIX "lib"
)

option(ENABLE_TSD "Enable TSD" ON)

if (CMAKE_HOST_WIN32)
    target_compile_definitions(slmp PRIVATE -DLIBSLMP_EXPORTS)
    target_link_libraries(slmp PRIVATE ws2_32)
    set(USE_WINDOWS_THREADS ON)
elseif (CMAKE_HOST_UNIX)
    if (ENABLE_TSD)
        set(CMAKE_THREAD_PREFER_PTHREAD ON)
        find_package(Threads)
        if (Threads_FOUND)
            target_link_libraries(slmp PUBLIC Threads::Threads)
            set(USE_POSIX_THREADS ON)
            set(HAVE_PTHREADS ON)
        endif ()
    endif ()
endif ()

include(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(strlcpy HAVE_STRLCPY)
if (NOT HAVE_STRLCPY)
    target_sources(slmp PRIVATE ${PROJECT_SOURCE_DIR}/strlcpy.c)
endif ()

include(CheckIncludeFile)
CHECK_INCLUDE_FILE(stdint.h HAVE_STDINT_H)
if (NOT HAVE_STDINT_H)
    target_include_directories(slmp SYSTEM PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hdrsup>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/slmp/hdrsup>
    )
endif ()

target_include_directories(slmp PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(slmp PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)

configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)                                           

install(
    TARGETS slmp
    EXPORT libslmp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT libslmp
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/slmp
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING REGEX ".*[.][Hh][^~]*$"
)

install(
    FILES ${PROJECT_BINARY_DIR}/config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/slmp
)

if (NOT HAVE_STDINT_H)
    install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/hdrsup/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/slmp/hdrsup
    )
endif ()
