#include "ddg.h"

MAT* createDdgMat(MAT* points){
    int numOfVectors = points->NUM_OF_VECTORS;
    MAT* symMat = createSymMat(points);
    MAT* ddgMat = initMat(numOfVectors, numOfVectors);
    int i;
    for(i = 0; i < numOfVectors; i++){
        ddgMat->vals[i][i] =  sumRow(points, i);
    }
    freeMat(symMat);
    return ddgMat;
}

double sumRow(MAT* mat, int row){
    double sum;
    int i;
    for (i = 0; i < mat->cols; i++){
        sum += mat->vals[row][i];
    }
    return sum;
}