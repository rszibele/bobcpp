cmake_minimum_required(VERSION 3.1.0)

project(bobcpp)

set(CMAKE_CXX_STANDARD 11)

# Only Qt implementation is available right now
set(USE_Qt 1)
if(USE_Qt)
    message("bobcpp will use the Qt implementation.")
    add_compile_definitions(BOBCPP_QT=1)
    find_package(Qt5 COMPONENTS Core Network REQUIRED)
    include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(bobcpp SHARED
    src/Exception.cpp
    src/QtClient.cpp
)

install(TARGETS bobcpp
        LIBRARY DESTINATION /usr/lib)
