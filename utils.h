#pragma once
#include <stdlib.h>
#include <stdio.h>


#define NUM_OF_VECTORS rows
#define VECTORS_LENGTH cols


typedef struct _mat
{
    double **vals;
    int rows;
    int cols;
}MAT;

MAT* initMat(int, int);
MAT* multiplyMat(MAT*, MAT*);
void freeMat(MAT*);
void printMat(MAT*);
