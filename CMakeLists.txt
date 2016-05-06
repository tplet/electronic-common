# Library name
set(NAME vendors)

# Config
set(${NAME}_RECURSE True)

# Files
file(GLOB_RECURSE FILES_CPP "*.cpp")
file(GLOB_RECURSE FILES_H "*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# Generate
generate_arduino_library(${NAME}
        SRCS ${FILES_CPP}
        HDRS ${FILES_H}
        BOARD ${BOARD}
        ARDLIBS ${ARDSLIBS}
)
