#include "utils.h"
#include "sym.h"
#include "ddg.h"

MAT* createDdgMat(MAT* points){
    int numOfVectors = points->NUM_OF_VECTORS;
    MAT* symMat = createSymMat(points);
    MAT* ddgMat = initMat(numOfVectors, numOfVectors);
    int i, j;
    for(i = 0; i < numOfVectors; i++){
        for(j = 0; j < numOfVectors; j++){
            if(i == j){
                ddgMat->vals[i][j] =  sumRow(points, i);
            }
        }
    }
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