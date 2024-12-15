cmake_minimum_required(VERSION 3.27)
project(CS204_HW3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS204_HW3 main.cpp
        UndoStack.h
        EmployeeProject2DLL.h
        EmployeeProject2DLL.cpp
        UndoStack.cpp)
