cmake_minimum_required(VERSION 3.0)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project (hello_world)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake OPTIONAL RESULT_VARIABLE HAS_CONAN)
conan_basic_setup()
include(os)

os_add_executable(hello "Hello world - OS included" main_jitter.cpp ../exp1.cpp)
os_add_drivers(hello boot_logger vga_emergency) #e1000
# os_add_plugins(hello autoconf)
os_add_stdout(hello vga_output)
os_add_stdout(hello default_stdout)
