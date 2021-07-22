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
    char my_char;
} var;

var my_var;

#pragma pdi off