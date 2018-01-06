cmake_minimum_required (VERSION 2.6)
project (Automated_Diferenciation)

set(Automated_Diferenciation_VERSION_MAJOR 1)
set(Automated_Diferenciation_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/libraries")
add_subdirectory (libraries)

#executable(s)

#add_executable(main.exe main.cpp)
add_executable(diffTree.exe libraries/diffTree.cpp)
add_executable(values.exe libraries/values.cpp)

#target_link_libraries(main values diffTree)

