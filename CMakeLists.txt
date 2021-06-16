cmake_minimum_required(VERSION 3.17)
project(HW7 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -Wall -pedantic-errors")

add_executable(HW7 Car.c Car.h Client.c Client.h DataBase.c DataBase.h Supplier.c Supplier.h Validation.c Validation.h main.c FillField.h FillField.c matam.c matam.h GenericDataStructures.c GenericDataStructures.h)