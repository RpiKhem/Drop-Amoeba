cmake_minimum_required(VERSION 3.16)

# Set the project name
project(Drop-Amoeba)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt5 and Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

# Add the executable
add_executable(Drop-Amoeba DropAmoeba/main.cpp DropAmoeba/amoebaview.cpp DropAmoeba/amoebamodel.cpp DropAmoeba/amoebapersist.cpp)

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Link to the Qt Core library
target_link_libraries(Drop-Amoeba PRIVATE Qt6::Widgets)

set_target_properties(Drop-Amoeba PROPERTIES
    WIN32_EXECUTABLE ON
)
