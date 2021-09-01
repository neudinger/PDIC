# PDIC

PDIC: [(IDL)](https://en.wikipedia.org/wiki/Interface_description_language) Transpiler Source-to-source compiler C/C++ to YAML Portable Data Interface Description

[![GitHub license](https://img.shields.io/badge/license-EUPL-blue.svg)](https://raw.githubusercontent.com/herotc/hero-rotation/master/LICENSE)

From C/C++ to Yaml Description

|Simple binary|Python library|
|:-:|:-:|
|static binary|Python 3|
|`./pdic file.c`|`import pdic; result:str = pdic.files_to_pdi()`|

```c++
#pragma pdi on

typedef struct Var8
{
#pragma pdi type : int64
    int my_int;
    char char_tab[20];
    char my_char;
} var;

#pragma pdi size:[42]
int **array_of_pointer_of_array[21];

var my_var;

#pragma pdi off
```

Will be see and describe as follow

```yml
structs:
 Var8:
  type: record
  name: Var8
  alias: [var]
  fieldsize: 3
  buffersize: 28
  packed: false
  members:
   char_tab: { type: array, subtype: char, size: 20 }
   my_char:
    offset: 24   
    type: char
   my_int:
    type: int64
data:
 array_of_pointer_of_array: { type: array, subtype:  { type: pointer, subtype:  { type: array, subtype: int, size: 42 } }, size: 21 }
 my_var:
  type: record
  name: Var8
  alias: [var]
  fieldsize: 3
  buffersize: 28
  packed: false
  members:
   char_tab: { type: array, subtype: char, size: 20 }
   my_char:
    offset: 24   
    type: char
   my_int:
    type: int64
```

Python Usage

```python
import os
import pathlib
import yaml
import pdic

here = pathlib.Path(__file__).parent.resolve()
# pip show -f pdic
if __name__ == "__main__":
    pdi_yml_description: str = pdic.files_to_pdi([os.path.join(here, "level_1.c"),
                                                  os.path.join(here, "level_2.c")])
    print(pdi_yml_description)
    print(yaml.dump(yaml.load(pdi_yml_description)))
```

## Index

1. [Abstract](/docs/1.0-Abstract.md)
2. [Usage](/docs/2.0-Requirement.md)
      1. [Binary](/docs/2.1-Binary.md)
      2. [Python](/docs/2.2-Python.md)
3. [Developpement](/docs/3.0-Developpement.md)
      - Code
      - Documentation
      - Test
      - Deploy
4. [Links](/docs/4.0-Links)
      - [Autre Documentation](/docs/5.1-Documentations.md)
      - Biblio
      - Code example
5. [Extra](/docs/5.0-Extra.md)
      - Clang LLVM
      - Mind Map
      - Graph
      - UML
6. Contact / Credits

Credits

Barre Kevin [neudinger](https://github.com/) (Software Scientist)

CEA pdi team
