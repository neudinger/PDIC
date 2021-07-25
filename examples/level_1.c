/*
 * File: level_1.c
 * Project: examples
 * File Created: Friday, 23rd July 2021 12:48:58 am
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Friday, 23rd July 2021 12:49:20 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

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