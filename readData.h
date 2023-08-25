#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Cord
{
    double value;
    struct Cord *next;
}CORD;

typedef struct Vector
{
    struct Vector *next;
    CORD *cords;
}VECTOR;

MAT* createDataMatrix(void);
void deleteList(VECTOR*);
void deleteCords(CORD*);
VECTOR* getInput(int*, int*);
