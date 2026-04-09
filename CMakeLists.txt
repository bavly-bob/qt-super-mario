cmake_minimum_required(VERSION 3.16)
project(qt-super-mario)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/player.cpp
  include/player.hpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE include
)

target_link_libraries(${PROJECT_NAME}
  Qt6::Widgets
)


