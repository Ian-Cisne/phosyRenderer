cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(Rasterizer)
add_executable(${PROJECT_NAME} src/main.cc )

add_subdirectory(lib/lodepng)

target_include_directories(${PROJECT_NAME} PUBLIC lib/lodepng)

target_link_directories(${PROJECT_NAME} PUBLIC lib/lodepng)

target_link_libraries(${PROJECT_NAME} lodepng)