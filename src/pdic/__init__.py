__author__ = "Barre Kevin"
__maintainer__ = "Barre kevin"
__credits__ = ["https://kevinbarre.fr/"]
__email__ = "kevin.barre@epitech.eu"

# -*- coding: utf-8 -*-
"""

## PDIC

PDIC: [(IDL)](https://en.wikipedia.org/wiki/Interface_description_language) Transpiler Source-to-source compiler C/C++ to YAML Portable Data Interface Description

Example:

example.py
```python
import os
import pathlib
import yaml
import pdic

code_source: str = '''
short notsee;
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
unsigned short notsee_either;
'''

if __name__ == '__main__':
    here = pathlib.Path(__file__).parent.resolve()
    pdi_yml_description_from_file: dict = yaml.load(pdic.file_to_pdi("examples/level_1.c"), Loader=yaml.FullLoader)
    pdi_yml_description_from_txt: dict = yaml.load(pdic.str_to_pdi(code_source), Loader=yaml.FullLoader)
    assert(pdi_yml_description_from_file == pdi_yml_description_from_txt)
    print(pdi_yml_description_from_txt)
```
"""

from .pypdic import file_to_pdi, str_to_pdi, files_to_pdi

try:
    from .__version__ import __version__  # noqa: F401, F40
except Exception:
    pass

__all__ = [
    "file_to_pdi",
    "str_to_pdi",
    "files_to_pdi"
]