cmake_minimum_required(VERSION 3.15)
project(S6 C)

set(CMAKE_C_STANDARD 99)

add_executable(S6 main.c "Sort my points/SortmyPoints.c" "Sort my points/SortmyPoints.h" "Protect my Variable/Protect.c" "Protect my Variable/Protect.h" "Do my Work/doMyWork.c" "Do my Work/doMyWork.h" "Shared ressource/SharedRessources.c" "Shared ressource/SharedRessources.h")