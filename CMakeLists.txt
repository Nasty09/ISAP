cmake_minimum_required(VERSION 3.16)
project(ISAP_2 LANGUAGES CXX)
find_package(PkgConfig REQUIRED)
pkg_check_modules(tommath REQUIRED IMPORTED_TARGET libtommath)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::tommath)
