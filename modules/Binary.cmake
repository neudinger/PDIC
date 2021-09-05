add_compile_options(-fno-rtti)
set(CLANG_LIB clang_bundled) # static
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
set(CMAKE_EXE_LINKER_FLAGS -static)
message(STATUS "The project will build a binary")
set(BINTARGET "${TARGET}.static")
add_executable(${BINTARGET}
    ${SRC}
)
target_link_libraries(${BINTARGET}
    PRIVATE
    ${CLANG_LIB} # clang lib
    pthread # multithreading
    m # math
    dl # dynamic loader
    z # zlib
)
add_dependencies(${BINTARGET} libclang-static-build)
set_property(TARGET ${BINTARGET} PROPERTY CXX_STANDARD 20)
unset(CLANG_LIB CACHE)