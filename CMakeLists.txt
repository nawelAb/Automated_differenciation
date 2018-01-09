cmake_minimum_required (VERSION 2.6)
project (Automated_Diferenciation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Automated_Diferenciation_VERSION_MAJOR 1)
set(Automated_Diferenciation_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/libraries")
add_subdirectory (libraries)

#executable(s)

add_executable(main tests.cpp)

#target_link_libraries(main libs)

