cmake_minimum_required(VERSION 2.6.0)

set(sources echosvr.c)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/../win32rsrc/rsrc.rc)
endif ()

add_executable(echosvr ${sources})

target_link_libraries(echosvr PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS echosvr
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

