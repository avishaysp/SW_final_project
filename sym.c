#include "sym.h"


MAT* createSymMat(MAT* points){
    int numOfVectors = points->NUM_OF_VECTORS;
    MAT* symMat = initMat(numOfVectors, numOfVectors);
    int i,j;
    double val;
    for (i = 0; i < numOfVectors; i++){
        for (j = 0; j < numOfVectors; j++){
            if(i == j){
                symMat->vals[i][j] = 0;
            } else{
                val = -0.5 * euclidianDistance(points->vals[i], points->vals[j], points->VECTORS_LENGTH);
                symMat->vals[i][j] = exp(val);
            }
        }
    }
    return symMat;
}

static euclidianDistance(double* vector1, double* vector2, int length) {
    double sum = 0.0;
    int i;
    for (i = 0; i < length; i++) {
        sum += pow(vector1[i] - vector2[i], 2);
    }
    return sqrt(sum);
}
