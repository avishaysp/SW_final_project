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

void freeMat(MAT* mat){
    int i;
    for(i = 0; i < mat->NUM_OF_VECTORS; i++){
        free(mat->vals[i]);
    }
    free(mat->vals);
    free(mat);
}

void printMat(MAT* mat){
    int i;
    int j;
    for(i = 0; i < mat->NUM_OF_VECTORS; i++) {
        for(j = 0; j <  mat->VECTORS_LENGTH; j++) {
            printf("%.4f ", mat->vals[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

MAT* multiplyMat(MAT* mat1, MAT* mat2){
    MAT* multiMat;
    int i, j, k;
    double sum;
    int numRows1 = mat1->NUM_OF_VECTORS;
    int numCols1 = mat1->VECTORS_LENGTH;
    int numCols2 = mat2->VECTORS_LENGTH;

    multiMat = initMat(numRows1, numCols2);

    for (i = 0; i < numRows1; i++) {
        for (j = 0; j < numCols2; j++) {
            sum = 0.0;
            for (k = 0; k < numCols1; k++) {
                sum += mat1->vals[i][k] * mat2->vals[k][j];
            }
            multiMat->vals[i][j] = sum;
        }
    }

    return multiMat;
}

