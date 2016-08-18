cmake_minimum_required(VERSION 3.3)
include(./cmake/functions.txt)

# Library name
set(NAME common)

# Files
file(GLOB_RECURSE ${NAME}_FILES_CPP "com/*.cpp")
file(GLOB_RECURSE ${NAME}_FILES_H "com/*.h")

# Ignores some paths
include(./cmake/ignore.txt)

if (ARDUINO_FOUND)
    ## Dependencies
    # RF24 (library)
    include_directories(./vendors/RF24)
    add_subdirectory(./vendors/RF24)
    # StandardCplusplus (add source file to library)
    include_directories(./vendors/StandardCplusplus)
    file(GLOB_RECURSE StandardCplusplus_FILES_CPP "vendors/StandardCplusplus/*.cpp")
    file(GLOB_RECURSE StandardCplusplus_FILES_H "vendors/StandardCplusplus/*.h")
    list(APPEND ${NAME}_FILES_CPP ${StandardCplusplus_FILES_CPP})
    list(APPEND ${NAME}_FILES_H ${StandardCplusplus_FILES_H})

    # Declare arduino library
    generate_arduino_library(
        ${NAME}
        SRCS ${${NAME}_FILES_CPP}
        HDRS ${${NAME}_FILES_H}
        BOARD ${BOARD}
        ARDLIBS SPI
        LIBS RF24
#        NO_AUTOLIBS
    )

    # StandardCplusplus (add root path of this library to include path)
    target_include_directories(${NAME} PUBLIC ./vendors/StandardCplusplus)

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

    # RF24
    if (${RF24_MOCK})
        # Use mock
        target_compile_definitions(${EXECUTABLE} PUBLIC -DRF24_MOCK)
        target_compile_definitions(${NAME} PUBLIC -DRF24_MOCK)
    else()
        # As external: must be installed before
        target_link_libraries(${NAME} rf24-bcm)
    endif()
endif()

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)
# Permit to include vendors files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC ./vendors)
