#include "utils.h"

MAT* initMat(int cols, int rows) {
    MAT* mat = (MAT*)calloc(1, sizeof(MAT));
    int i = 0;
    mat->cols = cols;
    mat->rows = rows;
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

static double multiplyVec(double* vec1, double* vec2, int length){
    int i;
    double sum = 0.0;
    for (i = 0; i < length; i++){
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

static double* getRow(MAT* mat,int j){
    int size = mat->NUM_OF_VECTORS;
    double* row = (double*)calloc(size, sizeof(double));
    int i;
    for (i = 0; i < size; i++){
        row[i] = mat->vals[i][j];
    }
    return row;
}

void printMat(MAT* mat){
    int i;
    int j;
    for(i = 0; i < mat->VECTORS_LENGTH; i++) {
        for(j = 0; j <  mat->NUM_OF_VECTORS; j++) {
            printf("%f ", mat->vals[j][i]);
        }
        printf("\n");
    }
}

MAT* multiplyMat(MAT* mat1, MAT* mat2){
    int vectorLength = mat1->VECTORS_LENGTH;
    int numOfVectors = mat2->NUM_OF_VECTORS;
    int multipleLength = mat1->NUM_OF_VECTORS;
    double* row;
    MAT* multiMat = initMat(numOfVectors, vectorLength);
    int i, j;
    for (i = 0; i < numOfVectors; i++){
        for (j = 0; j < vectorLength; j++){
            row = getRow(mat1, j);
            multiMat->vals[i][j] = multiplyVec(row, mat1->vals[i], multipleLength);
            free(row);
        }
    }
    return multiMat;
}