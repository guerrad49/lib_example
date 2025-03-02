cmake_minimum_required(VERSION 3.30)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_person test_person.cpp)

target_link_libraries(
    test_person
    GTest::gtest_main
    ${LIB}
)

target_include_directories(test_person PUBLIC
	"${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

add_executable(test_book test_book.cpp)

target_link_libraries(
    test_book
    GTest::gtest_main
    ${LIB}
)

target_include_directories(test_book PUBLIC
	"${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

include(GoogleTest)
gtest_discover_tests(test_person)
gtest_discover_tests(test_book)