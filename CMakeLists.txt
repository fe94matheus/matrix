cmake_minimum_required(VERSION 3.10)

project(MatrixProject LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the path for the include files
include_directories(include)

# Create an executable from the main source file
add_executable(MatrixProject src/main.cpp)

# Link any required libraries
target_link_libraries(MatrixProject mpfr gmp)
