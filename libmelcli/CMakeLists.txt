cmake_minimum_required(VERSION 2.6.0)

include(GNUInstallDirs)

file (GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/libmelcli.def ${CMAKE_CURRENT_SOURCE_DIR}/win32rsrc/rsrc.rc)
    set(LIBRARIES ${CMAKE_INSTALL_LIBDIR}/libmelcli${CMAKE_IMPORT_LIBRARY_SUFFIX})
else ()
    set(LIBRARIES ${CMAKE_INSTALL_LIBDIR}/libmelcli${CMAKE_SHARED_LIBRARY_SUFFIX})
endif ()

add_library(melcli SHARED ${sources})

target_compile_definitions(melcli PRIVATE -DLIBMELCLI_EXPORTS)

set_target_properties(melcli PROPERTIES
    PREFIX "lib"
    IMPORT_PREFIX "lib"
)

target_include_directories(melcli PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(melcli PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

include(CheckIncludeFile)
CHECK_INCLUDE_FILE(stdint.h HAVE_STDINT_H)
if (NOT HAVE_STDINT_H)
    target_include_directories(melcli SYSTEM PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hdrsup>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/melcli/hdrsup>
    )
endif ()

include(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(strlcpy HAVE_STRLCPY)
if (NOT HAVE_STRLCPY)
    target_sources(melcli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/strlcpy.c)
endif ()

target_link_libraries(melcli PRIVATE slmp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
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
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING REGEX ".*[.][Hh][^~]*$"
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/melcli
)

if (NOT HAVE_STDINT_H)
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/hdrsup/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/melcli/hdrsup
    )
endif ()

set(INCLUDE_DIRS ${CMAKE_INSTALL_INCLUDEDIR})
set(LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libmelcliConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PATH_VARS INCLUDE_DIRS LIBRARY_DIRS LIBRARIES
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libmelcliConfigVersion.cmake"
    VERSION 1.0.1
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libmelcliConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/libmelcliConfigVersion.cmake"
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
)

