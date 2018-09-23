cmake_minimum_required(VERSION 3.12)
project(project1csc173 C)

set(CMAKE_C_STANDARD 99 CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -Wall -Werror")

add_executable(project1csc173 main.c dfa.c IntHashSet.c LinkedList.c strdup.c nfa.c BitSet.c)