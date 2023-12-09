cmake_minimum_required(VERSION 2.6.0)

set(sources mcdemo.c)

if (CMAKE_HOST_WIN32)
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/../win32rsrc/rsrc.rc)
endif ()

add_executable(mcdemo ${sources})

target_link_libraries(mcdemo PRIVATE melcli)

include(GNUInstallDirs)
install(TARGETS mcdemo
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

