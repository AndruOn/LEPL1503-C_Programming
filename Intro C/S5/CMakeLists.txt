cmake_minimum_required(VERSION 3.15)
project(S5 C)

set(CMAKE_C_STANDARD 99)

add_executable(S5 main.c
        "Save Struct into file/StructToFile.c" "Save Struct into file/StructToFile.h"
        "Reading int in a binary file/Sum_file.c" "Reading int in a binary file/Sum_file.h"
        "Get and set on array stored in binary file/Get_Set_on_array.c" "Get and set on array stored in binary file/Get_Set_on_array.h"
        "File Copy/File_copy.c" "File Copy/File_copy.h")