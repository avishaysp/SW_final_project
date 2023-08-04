#include "utils.h"

MAT* initMat(int rows, int cols) {
    MAT* mat = (MAT*)calloc(1, sizeof(MAT));
    int i = 0;
    mat->rows = rows;
    mat->cols = cols;
    mat->vals = (double**)calloc(NUM_OF_VECTORS, sizeof(double*));
    for (; i < NUM_OF_VECTORS; i++) {
        mat->vals[i] = (double*)calloc(VECTORS_LENGTH, sizeof(double));
    }
    return mat;
}