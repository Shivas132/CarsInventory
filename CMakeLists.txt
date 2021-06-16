cmake_minimum_required(VERSION 3.17)
project(HW6 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -Wall -pedantic-errors -D DAVIS")

add_executable(HW6 Car.c Car.h Client.c Client.h DataBase.c DataBase.h Supplier.c Supplier.h Validation.c Validation.h main.c FillField.h FillField.c matam.c matam.h  BinarySearchTree.c BinarySearchTree.h)