#!/bin/bash

function compile() {
    SOURCE_FILES="main.cpp cryptography.cpp string_util.cpp"

    # Specify the name of the output executable
    OUTPUT_NAME="cryptography"

    # Compiler command (adjust as needed)
    COMPILER="g++"

    # Compilation flags (adjust as needed)
    COMPILE_FLAGS="-std=c++17 -lssl -lcrypto"

    # Compile each source file
    for SOURCE_FILE in $SOURCE_FILES; do
        OBJECT_FILE="${SOURCE_FILE%.cpp}.o"
        $COMPILER -c $SOURCE_FILE -o $OBJECT_FILE $COMPILE_FLAGS
        if [ $? -ne 0 ]; then
            echo "Compilation failed for $SOURCE_FILE"
            exit 1
        fi
    done

    # Link object files to create the executable
    $COMPILER $SOURCE_FILES -o $OUTPUT_NAME $COMPILE_FLAGS

    # Check if compilation was successful
    if [ $? -eq 0 ]; then
        echo "Compilation successful"
    else
        echo "Compilation failed."
    fi
}
if [ $1 == 'clean' ]
then
    rm -rf main.o cryptography.o matrices.o peda-session-sleep.txt string_util.o .gdb_history sort.o
# Define your source files
else
    compile
fi