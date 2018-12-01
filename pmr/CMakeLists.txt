cmake_minimum_required(VERSION 3.0)
project("Test PMR")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2")

# Build objects as libs to guarantee separate translation units
add_library(flush          OBJECT flush.cpp)
add_library(flush_pmr      OBJECT flush.cpp)
add_library(flush_stdalloc OBJECT flush.cpp)
add_library(default_pmr    OBJECT pmr_default.cpp)

# Executables
add_executable(test          main.cpp)
add_executable(test_pmr      main.cpp)
add_executable(test_stdalloc main.cpp)


# Define USE_PMR for pmr targets
target_compile_definitions(default_pmr PUBLIC USE_PMR)
target_compile_definitions(test_pmr    PUBLIC USE_PMR)
target_compile_definitions(flush_pmr   PUBLIC USE_PMR)

# Define USE_STD_ALLOC for stdalloc targets
target_compile_definitions(test_stdalloc    PUBLIC USE_STD_ALLOC)
target_compile_definitions(flush_stdalloc   PUBLIC USE_STD_ALLOC)

target_link_libraries(test          flush)
target_link_libraries(test_pmr      default_pmr flush_pmr)
target_link_libraries(test_stdalloc flush_stdalloc)
