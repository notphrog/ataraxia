cmake_minimum_required(VERSION 3.15)
project(ataraxia C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ataraxia
    src/main.cpp
    src/glad.c
    src/shader.h
    src/stb_image.cpp
    src/config.h
)

target_link_libraries(ataraxia PRIVATE
    glfw
    OpenGL::GL
)

add_custom_command(TARGET ataraxia POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:ataraxia>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:ataraxia>/assets"
    COMMENT "copying shaders and assets to build directory..."
)