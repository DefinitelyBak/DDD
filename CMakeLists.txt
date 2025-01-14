cmake_minimum_required(VERSION 3.30)
project(DDD VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(Poco)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Domain)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Adapters)

add_executable(main main.cpp)
target_link_libraries(main Poco::Poco)