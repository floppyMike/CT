cmake_minimum_required(VERSION 3.16)

project(CT VERSION 2.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(CustomLibrary/)
add_subdirectory(Ampel/)