cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common)

# Files
file(GLOB_RECURSE FILES_CPP "*.cpp")
file(GLOB_RECURSE FILES_H "*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# Define library ( need to use add_subdirectory(path) then target_link_libraries(lib1 lib2 common) on cmake root )
project("lib${NAME}")
add_library(${NAME} ${FILES_CPP} ${FILES_H})

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)

## Dependencies
# EEPROM
add_subdirectory(./vendors/eeprom/)
#target_link_libraries(${NAME} common)
