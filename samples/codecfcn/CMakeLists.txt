cmake_minimum_required(VERSION 2.6.0)

add_executable(codecfcn 
    codecfcn.c
)

target_link_libraries(codecfcn PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS codecfcn
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)
