cmake_minimum_required(VERSION 3.22.1)

project(HackAssembler)

add_executable(${PROJECT_NAME} main.c IOHelpers.c AssemblyTranslation.c Helpers.c FirstPassTranslation.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

