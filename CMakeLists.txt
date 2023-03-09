cmake_minimum_required(VERSION 3.10)

project(babel)
set(CMAKE_CXX_COMPILER_VERSION 12.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add files to server and client side
file(GLOB CL_FILES "client/main.cpp" "client/opus/*.cpp")
file(GLOB SV_FILES "server/main.cpp" "server/Server.cpp")

# Add your project source files here
add_executable(babel_server ${SV_FILES})
add_executable(babel_client ${CL_FILES})

# Link your project against asio
target_link_libraries(babel_server PRIVATE CONAN_PKG::asio CONAN_PKG::opus)
target_link_libraries(babel_client PRIVATE CONAN_PKG::qt CONAN_PKG::portaudio CONAN_PKG::opus)