cmake_minimum_required(VERSION 3.20)
project(pdi)
set(TARGET "pdic")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Use given `clang` toolchain.
set(CMAKE_CXX_COMPILER "${LLVM_TOOLS_BINARY_DIR}/clang++")
set(CMAKE_C_COMPILER "${LLVM_TOOLS_BINARY_DIR}/clang")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

# Set compiler flags.
include(HandleLLVMOptions)
# Use LLVM and clang headers.
include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)
include("./llvm-project-llvmorg-12.0.1/clang/cmake/modules/AddClang.cmake")

file(GLOB src
    "src/*.hpp"
    "src/*.cpp"
)

add_clang_executable(${TARGET} ${src})

target_link_libraries(${TARGET}
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangTooling
  clangASTMatchers
  )

# cmake .. ; make && ./pdic ../../PDI_test_parse.h --