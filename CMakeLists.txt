cmake_minimum_required (VERSION 2.6)
project (Automated_Diferenciation)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DCMAKE_CXX_COMPILER mpicxx)
set(DCMAKE_CC_COMPILER mpicc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} ${MPI_CXX_FLAGS}")

set(Automated_Diferenciation_VERSION_MAJOR 1)
set(Automated_Diferenciation_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/libraries")
add_subdirectory (libraries)

#executable(s)

add_executable(main tests.cpp)

#target_link_libraries(main libs ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(main PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(main PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

#
#cmake .. -DCMAKE_CXX_COMPILER=mpicxx -DCMAKE_CC_COMPILER=mpicc

