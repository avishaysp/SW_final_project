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
