# set the project name
project(FServerless)

# Add vcpkg toolchain
include(../vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(CURL CONFIG REQUIRED)
find_package(libcurl-simple-https CONFIG REQUIRED)
find_package(libhv CONFIG REQUIRED)

include_directories(include)

add_subdirectory(src)
