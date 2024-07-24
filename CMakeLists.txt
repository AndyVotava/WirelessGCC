cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
include(./lib/RF24/CMakeLists.txt)

project(proj)

pico_sdk_init()

add_subdirectory(lib)

add_executable(trans main.cpp)

target_link_libraries(trans pico_stdlib RF24 hardware_spi gcclib)

target_include_directories(trans PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/gcclib"
                          )

