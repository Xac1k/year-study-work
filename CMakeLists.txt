cmake_minimum_required(VERSION 3.10)
project(year-study-work)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Catch2 3 REQUIRED)
find_package(Crow REQUIRED)
find_package(CURL REQUIRED)


file(GLOB_RECURSE SOURCES "utils/*.cpp" "utils/*.h")
if (SOURCES)
    add_library(lib STATIC ${SOURCES})
else()
    message(WARNING "Folder 'utils' is empty or not found!")
endif()

add_executable(main main.cpp)

target_link_libraries(main
        PRIVATE
        lib
        Crow::Crow
        Catch2::Catch2WithMain
        pthread
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})