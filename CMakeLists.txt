cmake_minimum_required(VERSION 3.21)
set(TARGET "pdic")
project(${TARGET} VERSION 0.1)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEBUG "DEBUG option" OFF) # OFF by default
message(STATUS "DEBUG is " ${DEBUG})
option(SKBUILD "SKBUILD option" OFF) # OFF by default
message(STATUS "SKBUILD is " ${SKBUILD})
option(BINARY "BINARY option" OFF) # OFF by default
message(STATUS "BINARY is " ${BINARY})
option(TEST "TEST option" OFF) # OFF by default
message(STATUS "TEST is " ${TEST})


if(DEBUG)
  add_compile_definitions(DEBUG=True)
endif(DEBUG)

set(WORKDIR ${CMAKE_CURRENT_LIST_DIR}/src/pdic)
message(STATUS "WORKDIR in: ${WORKDIR}")

file(GLOB SRC
  "${WORKDIR}/*.hpp"
  "${WORKDIR}/*.cpp"
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)


if((BINARY OR TEST) OR SKBUILD)
  include(Builder)
else((BINARY OR TEST) OR SKBUILD)
  message("
  Please Use one at least one cmake flag \n\
  But only one between\n\
  - SKBUILD : python lib\n\
  - BINARY : embedded binary\n\
  - TEST : ctest\n\n\

  cmake -S . \n\
  -DSKBUILD:BOOL=OFF # or ON\n\
  -DBINARY:BOOL=ON  # or OFF\n\
  -DTEST:BOOL=OFF # or ON\n\
  -DDEBUG:BOOL=ON # or OFF\n\
  -B build "
  )
endif((BINARY OR TEST) OR SKBUILD)

set(ignoreMe "${SKBUILD}")

unset(DEBUG CACHE)
unset(SKBUILD CACHE)
unset(BINARY CACHE)
unset(TEST CACHE)