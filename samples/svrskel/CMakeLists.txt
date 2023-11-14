cmake_minimum_required(VERSION 2.6.0)

add_executable(svrskel
    svrmain.c
    server.c
)

target_link_libraries(svrskel PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS svrskel
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

