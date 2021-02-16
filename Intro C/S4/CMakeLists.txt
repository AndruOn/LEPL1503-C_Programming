cmake_minimum_required(VERSION 3.15)
project(S4 C)

set(CMAKE_C_STANDARD 99)

add_executable(S4 main.c "Simple Stack/Stack.c" "Simple Stack/Stack.h" "Comparing Functions/ComparingFunctiuns.c" "Comparing Functions/ComparingFunctiuns.h" "Filtering Linked List/FIlteringLL.c" "Filtering Linked List/FIlteringLL.h" "Ordered Linked List/OrderedLinkedList.c" "Ordered Linked List/OrderedLinkedList.h" "Advanced Stack/AdvancedStack.c" "Advanced Stack/AdvancedStack.h")