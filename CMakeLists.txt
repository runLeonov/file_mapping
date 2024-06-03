cmake_minimum_required(VERSION 3.28)
project(file_mapping C)

set(CMAKE_C_STANDARD 11)

add_executable(file_mapping
        src/main.c
        src/print_error.c
        src/create_file.c
        src/read_file.c
)

target_include_directories(file_mapping PRIVATE ${CMAKE_SOURCE_DIR}/src)
