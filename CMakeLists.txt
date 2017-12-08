cmake_minimum_required (VERSION 2.6)
project (Automated_Diferenciation)

set(Carrot_Juice_VERSION_MAJOR 1)
set(Carrot_Juice_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/libraries")
add_subdirectory (libraries)

#executable(s)

add_executable(main.exe main.cpp)

#target_link_libraries(main values diffTree)

