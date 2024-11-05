# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(HeatSimulation VERSION 1.0 LANGUAGES C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find HDF5 package (if available on the system)
find_package(HDF5 REQUIRED COMPONENTS CXX)

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

# Link HDF5 library and inih library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE HDF5::HDF5 inih)

# Specify include directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE
    ${HDF5_INCLUDE_DIRS}          # HDF5 include directories
    ${CMAKE_SOURCE_DIR}/include   # Custom include directory for project headers
    ${CMAKE_SOURCE_DIR}/libs/inih # Include directory for inih library
    ${CMAKE_SOURCE_DIR}/libs/pdi/pdi # Include directory for inih library
)
