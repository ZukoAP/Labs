cmake_minimum_required(VERSION 3.15)
project(Sems)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADER_FILES ../Sems/Students/Student.h)
add_executable(Sems ../Sems/Students/StudList.cpp ../Sems/Students/Student.h ../Sems/Students/DynArray.h)
#add_executable(1 main.c)