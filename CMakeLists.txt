cmake_minimum_required(VERSION 3.15)

# set the project name
project(FServerless)
# add_library(curl)
# include_directories(/path to /usr/include/x86_64-linux-gnu/curl/curl.h)
# include_directories(/usr/local/include/hv)

# add the executable
add_executable(control control.cpp FuncFactory.cpp FuncFactory.h function.cpp function.h node.cpp node.h config.h)
add_executable(client client.cpp config.h)
target_link_libraries(control -lhv)
target_link_libraries(client -lcurl)