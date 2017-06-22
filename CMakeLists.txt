#------------------ Caracteristicas generales del proyecto ------------------#

cmake_minimum_required(VERSION 2.8.9)
project(multiphaseLB)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)


# Bibliotecas externas: MPI
find_package(MPI REQUIRED)

# Bring the headers
include_directories(include ${MPI_INCLUDE_PATH})

# Compiler options for C
SET( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall" )


# Directorio con fuentes
add_subdirectory (src)
