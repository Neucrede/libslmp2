cmake_minimum_required(VERSION 2.6.0)

add_executable(echocli 
    echocli.c
)

target_link_libraries(echocli PRIVATE slmp)

include(GNUInstallDirs)
install(TARGETS echocli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/samples
)

