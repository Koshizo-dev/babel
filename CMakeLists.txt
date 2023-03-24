cmake_minimum_required(VERSION 3.10)

project(babel)
set(CMAKE_CXX_COMPILER_VERSION 12.2)
# set(CMAKE_CXX_FLAGS "-g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add files to server and client side
file(GLOB PROTOCOL_FILES "protocol/*.cpp" "protocol/packets/*.cpp" "protocol/fields/*.cpp" "protocol/serialization/*.cpp")
file(GLOB CL_FILES "client/**/*.cpp" "client/*.cpp" "protocol/client/**/*.cpp" "protocol/client/*.cpp")
file(GLOB SV_FILES "server/**/*.cpp" "server/*.cpp" "protocol/server/**/*.cpp" "protocol/server/*.cpp")

# Add your project source files here
add_executable(babel_server ${SV_FILES} ${PROTOCOL_FILES})
add_executable(babel_client ${CL_FILES} ${PROTOCOL_FILES})

# Link your project against asio
target_link_libraries(babel_server PRIVATE CONAN_PKG::asio CONAN_PKG::sqlite3)
target_link_libraries(babel_client PRIVATE CONAN_PKG::qt -lxcb-xinput -lpthread CONAN_PKG::portaudio CONAN_PKG::opus)
