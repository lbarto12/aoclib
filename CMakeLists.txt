cmake_minimum_required(VERSION 3.16)
project(aoclib LANGUAGES CXX)

file(GLOB_RECURSE AOCLIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/aoclib/*.cpp"
)
file(GLOB_RECURSE AOCLIB_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/aoclib/*.h"
)

add_library(aoclib STATIC ${AOCLIB_SOURCES} ${AOCLIB_HEADERS})
target_compile_features(aoclib PUBLIC cxx_std_20)

target_include_directories(aoclib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
