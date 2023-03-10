cmake_minimum_required(VERSION 3.0.0)
project(LOIS_1 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(
    GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.hpp"
)

option(${PROJECT_NAME}_build_tests "Build tests" ON)

add_library(${PROJECT_NAME} ${SOURCES})

add_executable(${PROJECT_NAME}_run main.cpp)

target_link_libraries(${PROJECT_NAME}_run ${PROJECT_NAME})


if(${PROJECT_NAME}_build_tests)
    enable_testing()

    include(FetchContent)

    message(STATUS "Fetching GTest...")

    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)

    set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    message(STATUS "GTest fetched")

    add_subdirectory(tests)
endif()