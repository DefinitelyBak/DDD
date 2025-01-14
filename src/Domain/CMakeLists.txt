set(sources
    Include/Exception.h 
    Include/Model.h
    Include/OrderLine.h
    Include/Batch.h
    Include/Utility.h
    Source/OrderLine.cpp
    Source/Batch.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_library(Domain ${sources})

target_include_directories(Domain
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>"
)