cmake_minimum_required(VERSION 2.6.0)

set(sources echocli.c)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/../win32rsrc/rsrc.rc)
endif ()

add_executable(echocli ${sources})

target_link_libraries(echocli PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS echocli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

