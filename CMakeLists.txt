cmake_minimum_required(VERSION 3.20) # VERSION 4.0 doesn't exist yet, 3.20 is safer
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add all your source files
add_executable(DSA_Project2
        main.cpp
        Course.cpp
        Course.h
)

target_link_libraries(DSA_Project2 Qt6::Widgets)

# IMPROVED COPY LOGIC:
# This ensures that whenever you build, the 'Data' folder
# is copied into the same folder as your DSA_Project2.exe
add_custom_command(TARGET DSA_Project2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Data"
        "$<TARGET_FILE_DIR:DSA_Project2>/Data")