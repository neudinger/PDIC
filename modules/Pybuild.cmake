# Python pybind build

FetchContent_Declare(
  pybind11
  URL https://github.com/pybind/pybind11/archive/refs/tags/v2.7.1.tar.gz
)
FetchContent_MakeAvailable(pybind11)
message(STATUS "The project is built using scikit-build")
set(PYTARGET "py${TARGET}")
# export LLVM_DIR=/media/kbarre/1d7f0a7c-34d5-4837-ad9a-95be3ec8cb53/Documents/dev/desciptor/pdic/src/llvm-project-llvmorg-12.0.1/build/
# export Clang_DIR=/media/kbarre/1d7f0a7c-34d5-4837-ad9a-95be3ec8cb53/Documents/dev/desciptor/pdic/src/llvm-project-llvmorg-12.0.1/build/
find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
set(LLVM_ENABLE_PLUGINS ON)
set(LLVM_LINK_COMPONENTS Support)
# # Set compiler flags.
# include(HandleLLVMOptions) # Hardcore warning
# # Use LLVM and clang headers.
include(AddLLVM)
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

pybind11_add_module(${PYTARGET} 
  MODULE
  ${SRC}
)
target_link_libraries(${PYTARGET}
  PRIVATE
  clang
  clangAST
  clangBasic
  clangFrontend
  clangTooling
  clangASTMatchers
  clangSerialization
  pthread # multithreading
  m # math
  dl # dynamic loader
  z # zlib
)
add_compile_definitions(SKBUILD=True)
set_property(TARGET ${PYTARGET} PROPERTY CXX_STANDARD 20)
# add_dependencies(${PYTARGET} libclang-static-build)
install(TARGETS ${PYTARGET} LIBRARY DESTINATION .)
