#include "ddg.h"

MAT* createDdgMat(MAT* points){
    int numOfVectors = points->NUM_OF_VECTORS;
    MAT* symMat = createSymMat(points);
    MAT* ddgMat = initMat(numOfVectors, numOfVectors);
    int i;
    for(i = 0; i < numOfVectors; i++){
        ddgMat->vals[i][i] =  sumRow(symMat, i);
    }
    freeMat(symMat);
    return ddgMat;
}

static double sumRow(MAT* mat, int row){
    double sum;
    int i;
    for (i = 0; i < mat->NUM_OF_VECTORS; i++){
        sum += mat->vals[i][row];
    }
    return sum;
}