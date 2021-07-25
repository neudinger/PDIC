# PDIC

PDIC: [(IDL)](https://en.wikipedia.org/wiki/Interface_description_language) Transpiler Source-to-source compiler C/C++ to YAML Portable Data Interface Description

## Abstract

Pronounce: PDI SEE

[Why clang ?](https://clang.llvm.org/index.html)

- Fast compiles and low memory use
- Expressive diagnostics (examples)
- GCC compatibility
- Modular library based architecture
- Support diverse clients (refactoring, static analysis, code generation, etc.)
- A real-world, production quality compiler
- A simple and hackable code base
- A single unified parser for C, Objective C, C++, and Objective C++
- Conformance with C/C++/ObjC and their variants

This project can see [PDI Portable Data Interface](https://gitlab.maisondelasimulation.fr/pdidev/pdi) representation in c/c++

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

### Simple

```sh
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-12.0.1.tar.gz
tar xvf llvmorg-12.0.1.tar.gz
mkdir build && cd build
cmake ..
make
```

### Complete

Follow: [LibTooling and LibASTMatchers](https://clang.llvm.org/docs/LibASTMatchersTutorial.html) installation tutorial if you want to contribute.

Use `gold` or `lld` because `ld` use too much ram

```sh
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-12.0.1.tar.gz
tar xvf llvmorg-12.0.1.tar.gz
cd llvm-project-llvmorg-12.0.1
mkdir build && cd build
cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DCMAKE_BUILD_TYPE=Release -DLLVM_USE_LINKER=gold
ninja
# ninja check       # Test LLVM only.
# ninja clang-test  # Test Clang only.
ninja install
cd ../..
mkdir build && cd build
cmake ..
make
```

## Examples

Files can be:

- file.c
- file.h
- file.hh / file.hpp
- file.cc / file.cpp

`--` is for [Compilation databases for Clang-based tools](https://eli.thegreenplace.net/2014/05/21/compilation-databases-for-clang-based-tools)
> Note that anything before the double dash “--” is an input to your LibTooling program, argv in main(), while anything after the double dash is an input to Clang itself (you won’t concern yourself with those). (source `LibTooling Example`)

```sh
./pdic ../examples/level_1.c --
```

pdic extract all information from [AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree) and write PDI representation.

```c
#pragma pdi on

int global_int;
char global_char;
void *global_pointer;
float **global_float_pointer_of_pointer;
int array[24];

// pointer to array of int of size 42
#pragma pdi type:int32; size:[42]
int **pointer_of_array;

double *array_of_pointers[21];

#pragma pdi type:uint64
#pragma pdi size:[10][10][10]
unsigned ****my_cube;

#pragma pdi off
```

Will be see and describe as follow

```yml
data:
 array: { type: array, subtype: int, size: 24 }
 array_of_pointers: { type: array, subtype:  { type: pointer, subtype: double }, size: 21 }
 global_char: 
  type: char
 global_float_pointer_of_pointer: { type: pointer, subtype:  { type: pointer, subtype: float } }
 global_int: 
  type: int
 global_pointer: { type: pointer, subtype: void }
 my_cube: { type: pointer, subtype:  { type: array, subtype: uint64, size: [10, 10, 10] } }
 pointer_of_array: { type: pointer, subtype:  { type: array, subtype: int32, size: 42 } }
```

You can find differents examples -> [Here](./examples/)

## Usefull links

[Clang API](http://man.hubwiz.com/manual/Clang)

### Clang / LLVM

#### Official documentation

- [Clang Plugins doc](https://clang.llvm.org/docs/ClangPlugins.html)
- [Clang Driver Design](https://clang.llvm.org/docs/DriverInternals.html)
- [RecursiveASTVisitor Tutorial](https://clang.llvm.org/docs/RAVFrontendAction.html)
  
#### Other documentation

- [Basics of AST manipulation](https://freecompilercamp.org/clang-AST-basics/)
- [Comment parser](https://danielbeard.io/2016/04/19/clang-frontend-action-part-1.html)
- [Hacking on Clang is surprisingly easy](https://mort.coffee/home/clang-compiler-hacking/)
- [understanding the clang ast](https://jonasdevlieghere.com/understanding-the-clang-ast/)
- [Clang Tutorial: The AST Matcher](https://xinhuang.github.io/posts/2015-02-08-clang-tutorial-the-ast-matcher.html)
- [Clang Tutorial: Finding Declarations](https://xinhuang.github.io/posts/2014-10-19-clang-tutorial-finding-declarations.html)

#### Clang Tutorial Part: LibTooling Example

1. [Part I](https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-i-introduction/)
2. [Part II](https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/)
3. [Part III](https://kevinaboos.wordpress.com/2013/07/29/clang-tutorial-part-iii-plugin-example/)

#### Pragma

- [Pragma token kind identifier](https://repo.hca.bsc.es/gitlab/rferrer/llvm-epi-0.8/-/commit/ea4f7c776194c96f8ece1456bc22102c6cbc9a33)
- [Ex custom pragma 'TritonAssert'](https://github.com/quarkslab/clang/commit/0163f52f70e4781ce99710575bb66943125357b2)

### Padding and packing in c/c++

- <https://fresh2refresh.com/c-programming/c-structure-padding/>
