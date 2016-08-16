cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common)

# Files
file(GLOB_RECURSE ${NAME}_FILES_CPP "com/*.cpp")
file(GLOB_RECURSE ${NAME}_FILES_H "com/*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

if (ARDUINO_FOUND)
    ## Dependencies
    # RF24
    include_directories(./vendors/RF24)
    add_subdirectory(./vendors/RF24)
    list(APPEND ${NAME}_FILES_CPP ${RF24_FILES_CPP})
    list(APPEND ${NAME}_FILES_H ${RF24_FILES_H})

    # Declare arduino library
    generate_arduino_library(
        ${NAME}
        SRCS ${${NAME}_FILES_CPP}
        HDRS ${${NAME}_FILES_H}
        BOARD ${BOARD}
        #ARDLIBS SPI
    )

else()

    # Define library ( need to use add_subdirectory(path) then target_link_libraries(lib1 lib2 common) on cmake root )
    project("lib${NAME}")
    add_library(${NAME} ${${NAME}_FILES_CPP} ${${NAME}_FILES_H})

    # Compiler
    set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    ## Dependencies
    # RF24
    #add_subdirectory(./vendors/RF24/)
    #target_link_libraries(${NAME} RF24)
    # RF24 (external: must be installed before)
    target_link_libraries(${NAME} rf24-bcm)
endif()

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)
# Permit to include vendors files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC ./vendors)

