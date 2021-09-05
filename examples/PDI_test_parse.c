#pragma pdi on

typedef struct
{
    int my_int;
    char my_char;
} var8;

typedef struct
{
    char my_char;
    int my_array[10][10];
} var9;

typedef struct
{
    char my_char;
    var9 v9;
} var10;

typedef struct
{
    char *my_pointer;
    int my_int;
} var16;

char var1;
short int var2;
int var3;
double var4;
float var5;
char var6[10];
int var7[10000][10000];

int *var11;     // pointer to int
int **var12;    // pointer to int pointer
int **var13;    // pointer to 32bit array of int
int *var14[32]; // array of int pointers

var8 var15;

#pragma pdi off