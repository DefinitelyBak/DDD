set(sources
	Include/ORM.h
    Include/QueryObjects/OrderLineQuery.h
	Source/ORM.cpp
    Source/QueryObjects/OrderLineQuery.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_library(Adapters ${sources})

target_include_directories(Adapters
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>"
)

find_package(Poco)
target_link_libraries(Adapters PRIVATE Domain Poco::Poco)