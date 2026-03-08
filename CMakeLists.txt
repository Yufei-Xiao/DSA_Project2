cmake_minimum_required(VERSION 4.0)
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)
add_executable(DSA_Project2 main.cpp
        Courses.cpp
        Courses.h)
target_link_libraries(DSA_Project2 Qt6::Widgets)