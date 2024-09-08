set(CMAKE_PREFIX_PATH C:/Projects/DDD/Dependencies/build_poco/Poco)

find_package(Poco REQUIRED Data DataSQLite Foundation Net Util)

add_library(
    Database
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/ORM/OrderLineMapping.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/ORM/BatchMapping.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/ConvertDate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Repository/Repository.cpp
)

target_include_directories(
    Database 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../External)

target_link_libraries(
    Database
  PUBLIC
    Model
    Poco::DataSQLite
    Poco::Data
)
