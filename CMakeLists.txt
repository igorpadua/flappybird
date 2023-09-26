cmake_minimum_required(VERSION 3.5)

project(flappybird LANGUAGES CXX)

IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.2 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(flappybird main.cpp
    flappy.hpp flappy.cpp)

set(RESOURCE_FILES
    resources/img/flappy.png
    resources/img/pipe.png
    resources/img/background.png
    resources/font/flappybird.ttf
)

include(GNUInstallDirs)
install(TARGETS flappybird
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(flappybird sfml-graphics sfml-audio)
