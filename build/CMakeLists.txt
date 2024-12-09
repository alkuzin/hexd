cmake_minimum_required(VERSION 3.10.0)

# Set project name
set (PROJECT_NAME hexd)
project (${PROJECT_NAME})

# Check if the compiler is gcc
if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires gcc as the C compiler!")
endif()

set(CMAKE_C_STANDARD 23)          # Using C23 standard
set(CMAKE_C_STANDARD_REQUIRED ON) # Enforce the standard
set(CMAKE_C_EXTENSIONS OFF)       # Disable compiler-specific extensions

# Set paths
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../include)
set(SRC_DIR     ${CMAKE_SOURCE_DIR}/../src)

# Set source files
set(SRCS
    "${SRC_DIR}/hexd.c"
    "${SRC_DIR}/main.c"
)

add_executable(${PROJECT_NAME} ${SRCS})

# Set compiler flags
set(CFLAGS -Wall -Werror -Wextra -Wpedantic -Wconversion -Wshadow -fanalyzer -g -O2)
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})

# Set include directories
include_directories(${INCLUDE_DIR})