# IF MSVC
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
# SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.dll.a;.dll")
# target_compile_options(your_target_name [PUBLIC|PRIVATE] /MT)
# target_link_options(your_target_name [PUBLIC|PRIVATE] /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
# IF MFC
# https://cmake.org/cmake/help/latest/variable/CMAKE_MFC_FLAG.html
# set(CMAKE_MFC_FLAG 1)


if(SKBUILD) # Python pybind build
  include(Pybuild)
endif(SKBUILD)

if(BINARY OR TEST) # pdic portable binary
  include(LibClang)
  message(STATUS "clang binary_dir is " ${binary_dir})
  link_directories(
    ${binary_dir} # some lib are there
    ${binary_dir}/_all_archives # other are there
    ${binary_dir}/libclang-copied/lib # all are copied there
  )

  include_directories(
    ${binary_dir}/_deps/clang_sources-src/include
    ${binary_dir}/_deps/libclang_prebuilt-src/include
  )

  if(BINARY) # pdic portable binary
    include(Binary)
  endif(BINARY)
  if(TEST) # cmake google test
    include(Tests)
  endif(TEST)
endif(BINARY OR TEST)




