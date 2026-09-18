cmake_minimum_required(VERSION 3.26.0)
project(hello_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hello_window 
  src/config.h
  src/config.cpp
  src/main.cpp
  src/glad.c
  src/constants.cpp
  src/factories/factory.cpp
  src/factories/mesh_factory.cpp
  src/systems/render_system.cpp
  src/systems/motion_system.cpp
  src/systems/camera_system.cpp
  src/view/shader.cpp
  src/controller/app.cpp
)

target_include_directories(hello_window PRIVATE dependencies)
target_link_libraries(hello_window ${GLFW3_LIBRARY} OpenGL::GL)