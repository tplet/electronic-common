cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common)

# Files
file(GLOB_RECURSE FILES_CPP "com/*.cpp")
file(GLOB_RECURSE FILES_H "com/*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# Define library ( need to use add_subdirectory(path) then target_link_libraries(lib1 lib2 common) on cmake root )
project("lib${NAME}")
add_library(${NAME} ${FILES_CPP} ${FILES_H})

# Compiler
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)

## Dependencies
# RF24
#add_subdirectory(./vendors/RF24/)
#target_link_libraries(${NAME} RF24)
# RF24 (external: must be installed before)
target_link_libraries(${NAME} rf24-bcm)
