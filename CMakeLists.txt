# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(HeatSimulation VERSION 1.0 LANGUAGES C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adding PDI
find_package(PDI REQUIRED)

# Glob all .cpp files in src and src/sources directories
file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/sources/*.cpp"
)

# Add ini.c as a static library and specify the language as C
add_library(inih STATIC ${CMAKE_SOURCE_DIR}/libs/inih/ini.c)
set_target_properties(inih PROPERTIES LINKER_LANGUAGE C)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(HeatSimulation PUBLIC ON)

# Link and inih library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE inih)

# Specify include directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include   # Custom include directory for project headers
    ${CMAKE_SOURCE_DIR}/libs/inih # Include directory for inih library
)
