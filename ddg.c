#include "ddg.h"

static double sumRow(MAT* mat, int row){
    double sum = 0.0;
    int i;
    for (i = 0; i < mat->NUM_OF_VECTORS; i++){
        sum += mat->vals[row][i];
    }
    return sum;
}

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
