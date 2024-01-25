cmake_minimum_required(VERSION 3.5)

project(qt_1 LANGUAGES CXX)
include(GNUInstallDirs)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)
add_executable(qt_1 main.cpp
    utils.cpp)

install(TARGETS qt_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
