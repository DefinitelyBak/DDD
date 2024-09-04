add_library(
    Model
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Batch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OrderLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OrderLineHash.cpp
)

target_include_directories(
    Model 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../External)
