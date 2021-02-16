cmake_minimum_required(VERSION 3.15)
project(S3_C C)

set(CMAKE_C_STANDARD 99)

add_executable(S3_C main.c "Structures and Pointers/Structures and Pointers to structures.c" "Structures and Pointers/Structures and Pointers to structures.h" "Simple LinkedList/SImpleLinkedList.c" "Simple LinkedList/SImpleLinkedList.h" BinaryTree/BinaryTree.c BinaryTree/BinaryTree.h "calloc(3) malloc(3)/CallocMalloc.c" "calloc(3) malloc(3)/CallocMalloc.h")