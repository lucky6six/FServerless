project(faasruntime)

file(GLOB _src *.h *.cpp)

add_executable(${PROJECT_NAME} ${_src})

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(_lib_hv hv_static)
else()
    set(_lib_hv hv)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE libcurl-simple-https ${_lib_hv})