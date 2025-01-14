include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(sources
    Unit/TestAllocate.cpp
    Unit/TestBatches.cpp
    Integration/TestOrm.cpp
    Integration/TestRepository.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})
add_executable( Tests ${sources})

find_package(Poco)
target_link_libraries(
    Tests
  PRIVATE
    GTest::gtest_main
    Domain
    Adapters
    Poco::Poco
)

include(GoogleTest)
gtest_discover_tests(Tests)

