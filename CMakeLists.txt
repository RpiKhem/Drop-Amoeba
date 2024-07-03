cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Drop-Amoeba)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find Qt5 and Qt6 packages
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)

# Add the executable
add_executable(Drop-Amoeba DropAmoeba/main.cpp DropAmoeba/amoebaview.cpp DropAmoeba/amoebamodel.cpp DropAmoeba/amoebapersist.cpp)

# Link to the Qt Core library
target_link_libraries(Drop-Amoeba Qt6::Core)
