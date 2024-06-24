include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/1d17ea141d2c11b8917d2c7d029f1c4e2b9769b2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
  example1_test
  example1_test.cc
  scanner_test.cpp
)

target_link_libraries(
  example1_test
  GTest::gtest_main
  Frontend
)

include(GoogleTest)
gtest_discover_tests(example1_test)