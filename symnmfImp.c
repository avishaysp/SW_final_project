#include "symnmfImp.h"
#include "ncm.h"



MAT* createHMat(MAT* initializeH, MAT* normMAT, int maxIter, double eps){
    MAT* nextMat = getNext(normMAT, initializeH);
    while (frobeniusNorm(nextMat, initializeH) >= eps || maxIter > 0){
        initializeH = nextMat;
        freeMat(nextMat);
        nextMat = getNext(normMAT, initializeH);
    }
    freeMat(nextMat);
    return initializeH;
}

double frobeniusNorm(MAT* mat1, MAT* mat2){
    int i, j;
    double norm;
    for(i = 0; i < mat1->cols; i++){
        for(j = 0; j <  mat1->rows; i++){
            norm =+ pow(mat1->vals[i][j] - mat2->vals[i][j], 2);
        }
    }
    return sqrt(norm);
}

MAT* transformMat(MAT* mat){
    MAT* tranMat = initMat(mat->rows, mat->cols);
    int i,j;
    for (i = 0; i < tranMat->cols; i++){
        for (j = 0; j < tranMat->rows; j++){
            tranMat->vals[i][j] = mat->vals[j][i];
        }
    }
    return tranMat;
}

MAT* createNext(MAT* initializeH, MAT* numeratorMat, MAT* denominatorMat){
    MAT* next = initMat(initializeH->cols, initializeH->rows);
    int i,j;
    for (i = 0; i < next->cols; i++){
        for (j = 0; j < next->rows; j++){
            next->vals[i][j] = initializeH->vals[i][j] * (1 - BETA + BETA * (numeratorMat->vals[i][j] / denominatorMat->vals[i][j]));
        }
    }
    return next;
}

MAT* getNext(MAT* normMAT, MAT* initializeH){
    MAT* numeratorMat = multiplyMat(normMAT, initializeH);
    MAT* transformMAt = transformMat(initializeH);
    MAT* denominatorMatLeft = multiplyMat(initializeH, transformMAt);
    MAT* denominatorMat = multiplyMat(denominatorMatLeft, initializeH);
    MAT* nextMat = createNext(initializeH, numeratorMat, denominatorMat);
    freeMat(numeratorMat);
    freeMat(transformMAt);
    freeMat(denominatorMatLeft);
    freeMat(denominatorMat);
    return nextMat;
}
