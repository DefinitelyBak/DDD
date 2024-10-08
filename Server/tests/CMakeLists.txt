include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  Tests
  ## Model
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/Model/TestBatches.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/Model/Auxiliary.cpp
  ## Database
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/Database/TestORM.cpp
)

target_include_directories(
    Tests 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(
    Tests
  PRIVATE
    Model
    Database
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)

