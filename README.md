# PDIC

PDIC: [(IDL)](https://en.wikipedia.org/wiki/Interface_description_language) Transpiler Source-to-source compiler C/C++ to YAML Portable Data Interface Description

## Abstract

Pronounce: PDI SEE

This project can see [PDI Portable Data Interface](https://gitlab.maisondelasimulation.fr/pdidev/pdi) Representation in c/c++

## Descriptions

[![GitHub license](https://img.shields.io/badge/license-EUPL-blue.svg)](https://raw.githubusercontent.com/herotc/hero-rotation/master/LICENSE)

## Usage

```sh
./pdic ../PDI_test_parse.h --
```

`PDI_test_parse.yml` will be created

## Installation

Dependencies:

- cmake
- ninja
- make
- all clang and llvm tools
- boost

Follow: [LibTooling and LibASTMatchers](https://clang.llvm.org/docs/LibASTMatchersTutorial.html) installation tutorial if you want to contribute.

Use `gold` or `lld` because `ld` use too much ram

```sh
cd llvm-project-llvmorg-12.0.1
mkdir build && cd build
cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DCMAKE_BUILD_TYPE=Release -DLLVM_USE_LINKER=gold
```

Or install clang and llvm on your system

Compile PDIC project

```sh
cd pdic
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-12.0.1.tar.gz
tar xvf llvmorg-12.0.1.tar.gz
mkdir build && cd build
cmake ..
make
```

## Example

Files can be:

- file.c
- file.h
- file.hh / file.hpp
- file.cc / file.cpp

```c
#pragma pdi on

int global_int;
char global_char;
void *global_pointer;
float **global_float_pointer_of_pointer;

// pointer to array of int of size 42
#pragma pdi type:int32, size:[42]
int *pointer_of_array;

double *array_of_pointer[21];

#pragma pdi type:int128
#pragma pdi size:[10][10][10]
unsigned ****my_cube;

#pragma pdi off
```

Will be see and describe

```yml
data:
 array: { type: array, subtype: int, size: 24 }
 array_of_pointer: { type: array, subtype:  { type: pointer, subtype: double }, size: 21 }
 global_char: 
  type: char
 global_float_pointer_of_pointer: { type: pointer, subtype:  { type: pointer, subtype: float } }
 global_int: 
  type: int
 global_pointer: { type: pointer, subtype: void }
 my_cube: { type: pointer, subtype:  { type: array, subtype: int128, size: [10, 10, 10] } }
 pointer_of_array: { type: pointer, subtype: int }
```

```sh
./pdic ../examples/level_1.c --
```

## Usefull link

### Clang / LLVM

- <https://jonasdevlieghere.com/understanding-the-clang-ast/#asttraversal>
- <https://blog.quarkslab.com/implementing-a-custom-directive-handler-in-clang.html>
- <https://clang.llvm.org/docs/RAVFrontendAction.html>
- <https://opensource.apple.com/source/clang/clang-425.0.24/src/tools/clang/docs/RAVFrontendAction.html>
  RecursiveASTVisitor Tutorial
- <https://freecompilercamp.org/clang-AST-basics/>
- <https://danielbeard.io/2016/04/19/clang-frontend-action-part-1.html>
- <https://opensource.apple.com/source/clang/clang-500.2.76/src/tools/clang/docs/RAVFrontendAction.rst.auto.html>

### Padding and packing in c/c++

- <https://grandidierite.github.io/structure-alignment-and-packing-in-C-programming/>
- <https://www.delftstack.com/howto/c/struct-alignment-in-c/>
- <https://fresh2refresh.com/c-programming/c-structure-padding/>
- <https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/>