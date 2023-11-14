cmake_minimum_required(VERSION 2.6.0)

add_executable(echosvr 
    echosvr.c
)

target_link_libraries(echosvr PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS echosvr
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

