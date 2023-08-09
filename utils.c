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
    for(i = 0; i < mat->rows; i++){
        free(mat->vals[i]);
    }
    free(mat->vals);
    free(mat);
}

MAT* multiplyMat(MAT* mat1, MAT* mat2){
    int vectorLength = mat1->VECTORS_LENGTH;
    int numOfVectors = mat2->NUM_OF_VECTORS;
    int multipleLength = mat1->NUM_OF_VECTORS;
    double* columns;
    MAT* multiMat = initMat(vectorLength, numOfVectors);
    int i, j;
    for (i = 0; i < vectorLength; i++){
        for (j = 0; j < vectorLength; j++){
            columns = getColumns(mat2, j);
            multiMat->vals[i][j] = vecMulti(mat1->vals[i], columns, multipleLength);
            free(columns);
        }
    }
    return multiMat;
}

double multiplyVec(double* vec1, double* vec2, int length){
    int i;
    double sum;
    for (int i = 0; i < length; i++){
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

double* getColumns(MAT* mat,int j){
    int size = mat->rows;
    double* col = (double*)calloc(size, sizeof(double));
    int i;
    for (i = 0; i < size; i++){
        col[i] = mat->vals[i][j];
    }
    return col;
}

void printMat(MAT* mat){
    int i;
    int j;
    for(i = 0; i < mat->rows; i++) {
        for(j = 0; j <  mat->cols; j++) {
            printf("%f, ", mat->vals[i][j]);
        }
        printf("\n");
    }
}