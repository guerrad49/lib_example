cmake_minimum_required(VERSION 3.30)

project(
    practice
    VERSION 1.0
    LANGUAGES CXX
)

# Enable C++17 or higher.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create library.
set(LIB Birthdays)
add_subdirectory(src)

# Add testing.
if (BUILD_TESTING)
    add_subdirectory(tests/cpp)
endif()

# Add examples.
option(BUILD_EXAMPLES "Build the examples." OFF)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add python interface.
option(BUILD_PYBIND "Build python interface." OFF)
if (BUILD_PYBIND)
    add_subdirectory(python)
endif()

# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
