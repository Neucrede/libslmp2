cmake_minimum_required(VERSION 2.6.0)

set(sources codecfcn.c)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/../win32rsrc/rsrc.rc)
endif ()

add_executable(codecfcn ${sources})

target_link_libraries(codecfcn PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS codecfcn
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)
