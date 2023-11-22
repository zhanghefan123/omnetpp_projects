cmake_minimum_required(VERSION 3.25)
project(DelayTolerantNetwork)

set(CMAKE_CXX_STANDARD 14)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("include linux directory")
    include_directories(/home/zhf/Tools/omnetpp-6.0.1/include)
else()
    message("include mac directory")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/additional_headers)
endif ()

include_directories(inet/src)
add_definitions(-DWITH_OSG)
add_definitions(-DWITH_OSGEARTH)

file(GLOB_RECURSE ALL_C_FILES_IN_INET ${CMAKE_CURRENT_SOURCE_DIR}/inet/src/*.cc)
file(GLOB_RECURSE ALL_C_FILES_IN_MULTILAYER_SATELLITES ${CMAKE_CURRENT_SOURCE_DIR}/Multilayer-satellites/*.cc)
add_executable(lipsin_exe ${ALL_C_FILES_IN_INET} ${ALL_C_FILES_IN_MULTILAYER_SATELLITES})