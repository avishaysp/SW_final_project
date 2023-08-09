#include "ncm.h"

MAT* createNsmMat(MAT* points){
    int numOfVectors = points->NUM_OF_VECTORS;
    MAT* symMat = createSymMat(points);
    MAT* ddgMat = createDdgMat(points);
    MAT* nsmMat = initMat(numOfVectors, numOfVectors);
    int i;
    for(i = 0; i < numOfVectors; i++){
        ddgMat->vals[i][i] = 1 / (sqrt(ddgMat->vals[i][i]));
    }
    nsmMat = multiplyMat(multiplyMat(ddgMat, symMat), ddgMat);
    freeMat(symMat);
    freeMat(ddgMat);
    return nsmMat;
}