cmake_minimum_required(VERSION 2.6.0)

project(melcli)

include(GNUInstallDirs)

file (GLOB sources ${PROJECT_SOURCE_DIR}/*.c ${PROJECT_SOURCE_DIR}/*.cpp)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${PROJECT_SOURCE_DIR}/libmelcli.def ${PROJECT_SOURCE_DIR}/win32rsrc/rsrc.rc)
endif ()

add_library(melcli SHARED ${sources})

target_compile_definitions(melcli PRIVATE -DLIBMELCLI_EXPORTS)

set_target_properties(melcli PROPERTIES
    PREFIX "lib"
    IMPORT_PREFIX "lib"
)

target_include_directories(melcli PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/melcli>
)

target_include_directories(melcli PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)

include(CheckIncludeFile)
CHECK_INCLUDE_FILE(stdint.h HAVE_STDINT_H)
if (NOT HAVE_STDINT_H)
    target_include_directories(melcli SYSTEM PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hdrsup>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/melcli/hdrsup>
    )
endif ()

include(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(strlcpy HAVE_STRLCPY)
if (NOT HAVE_STRLCPY)
    target_sources(melcli PRIVATE ${PROJECT_SOURCE_DIR}/strlcpy.c)
endif ()

target_link_libraries(melcli PRIVATE slmp)

configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

install(
    TARGETS melcli
    EXPORT libmelcli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/melcli
)

install(
    EXPORT libmelcli
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/melcli
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING REGEX ".*[.][Hh][^~]*$"
)

install(
    FILES ${PROJECT_BINARY_DIR}/config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/melcli
)

if (NOT HAVE_STDINT_H)
    install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/hdrsup/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/melcli/hdrsup
    )
endif ()
