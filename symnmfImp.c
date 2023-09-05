#include "symnmfImp.h"
#include "ncm.h"


static double frobeniusNorm(MAT* mat1, MAT* mat2){
    int i, j;
    double norm = 0.0;
    for(i = 0; i < mat1->rows; i++){
        for(j = 0; j <  mat1->cols; i++){
            norm += pow(mat1->vals[i][j] - mat2->vals[i][j], 2);
        }
    }
    return sqrt(norm);
}

static MAT* transformMat(MAT* mat){
    MAT* tranMat = initMat(mat->cols, mat->rows);
    int i,j;
    for (i = 0; i < tranMat->rows; i++){
        for (j = 0; j < tranMat->cols; j++){
            tranMat->vals[i][j] = mat->vals[j][i];
        }
    }
    return tranMat;
}

static MAT* createNext(MAT* initializedH, MAT* numeratorMat, MAT* denominatorMat){
    MAT* next = initMat(initializedH->rows, initializedH->cols);
    int i,j;
    for (i = 0; i < next->rows; i++){
        for (j = 0; j < next->cols; j++){
            next->vals[i][j] = initializedH->vals[i][j] * (1 - BETA + BETA * (numeratorMat->vals[i][j] / denominatorMat->vals[i][j]));
        }
    }
    return next;
}

static MAT* getNext(MAT* normMAT, MAT* initializedH){
    MAT* numeratorMat = multiplyMat(normMAT, initializedH);
    MAT* transformMAt = transformMat(initializedH);
    MAT* denominatorMatLeft = multiplyMat(initializedH, transformMAt);
    MAT* denominatorMat = multiplyMat(denominatorMatLeft, initializedH);
    MAT* nextMat = createNext(initializedH, numeratorMat, denominatorMat);
    freeMat(numeratorMat);
    freeMat(transformMAt);
    freeMat(denominatorMatLeft);
    freeMat(denominatorMat);
    return nextMat;
}

MAT* createHMat(MAT* initializedH, MAT* normMAT, int maxIter, double eps){
    MAT* nextMat = getNext(normMAT, initializedH);
    while (frobeniusNorm(nextMat, initializedH) >= eps || maxIter > 0){
        initializedH = nextMat;
        freeMat(nextMat);
        nextMat = getNext(normMAT, initializedH);
    }
    freeMat(nextMat);
    return initializedH;
}
