/*
 * File: level_3.cpp
 * Project: examples
 * File Created: Sunday, 25th July 2021 8:04:25 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Sunday, 25th July 2021 8:04:55 pm
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

#pragma pdi on

typedef struct Structure1
{
    int id1;          // 4 Bytes
    int id2;          // 4 Bytes
    char name;        // 1 Bytes
    char c;           // 1 Bytes
    float percentage; // 4 Bytes
    template <typename T>
    operator T *()
    {
        return new T();
    }
} St1;

struct structure2
{
    int id1;          // 4 Bytes
    char name;        // 1 Bytes
    int id2;          // 4 Bytes
    char c;           // 1 Bytes
    float percentage; // 4 Bytes
    St1 *val = new St1();
} __attribute__((packed));


typedef struct // <- warning: will be printed cause of Anonymous struct used but alias will be used
{
    struct structure2 st2;
    St1 my_st1;
} St3;

struct structure2 dd;
St3 global_st3;

#pragma pdi off