FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
message(STATUS "The project will build google tests")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_compile_options(-fno-rtti)

list(APPEND FileName c_yaml_test)

add_compile_definitions(GOOGLE_TEST=True)


get_filename_component(WORKDIR "${CMAKE_CURRENT_LIST_DIR}" PATH)
set(WORKDIR ${WORKDIR}/src/pdic)
include_directories(
  ${WORKDIR}
)

include(GoogleTest)
enable_testing()
foreach(X IN LISTS FileName)
    message(STATUS "Build TEST: ${X}")
    add_executable(
      ${X}
      tests/${X}.cc
      ${SRC}
    )
    target_link_libraries(${X}
      PRIVATE
      gtest_main # Google test lib
      clang_bundled # Dynamic clang lib
      pthread # multithreading
      m # math
      dl # dynamic loader
      z # zlib
    )
  add_dependencies(${X} libclang-static-build)
  set_property(TARGET ${X} PROPERTY CXX_STANDARD 20)
  gtest_discover_tests(${X})
  add_test(NAME ${X} COMMAND ${X})
endforeach()