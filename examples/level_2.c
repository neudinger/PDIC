/*
 * File: level_2.c
 * Project: examples
 * File Created: Friday, 23rd July 2021 12:48:59 am
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Friday, 23rd July 2021 12:51:05 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

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