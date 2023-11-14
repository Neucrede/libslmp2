cmake_minimum_required(VERSION 2.6.0)

add_executable(mcdemo 
    mcdemo.c
)

target_link_libraries(mcdemo PRIVATE melcli)

include(GNUInstallDirs)
install(TARGETS mcdemo
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

