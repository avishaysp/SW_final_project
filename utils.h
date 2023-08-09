#include <stdlib.h>

#define NUM_OF_VECTORS cols
#define VECTORS_LENGTH rows


typedef struct _mat
{
    double **vals;
    int cols;
    int rows;
}MAT;

typedef struct _vec
{
    double *vals;
    int length;
}VECTOR;


MAT* initMat(int, int);
MAT* multiplyMat(MAT*, MAT*);
double multiplyVec(double*, double*, int);
double* getColumns(MAT*,int);
void freeMat(MAT*);