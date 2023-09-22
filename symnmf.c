#include "symnmf.h"

MAT* executeOperate(MatFunction goal, MAT* cVectors){
    return goal(cVectors);
}

MAT* executeSymnmf(MAT* cHInitMat, MAT* cNormMat, int iter, double eps){
    return createHMat(cHInitMat, cNormMat, iter, eps);
}

int main(int argc, char** argv) {
    MAT* result;
    MAT* matrix = readCSVtoMatrix(argv[2]);
    if (argc > 3){
        exit(1);
    }

    if (strcmp(argv[1], "sym") == 0){
        result = createSymMat(matrix);
    }

    else if (strcmp(argv[1], "ddg") == 0){
        result = createDdgMat(matrix);
    }

    else if (strcmp(argv[1], "norm") == 0){
        result = createNsmMat(matrix);
    }
    else{
        printf("An Error has Occured");
        exit(1);
    }
    printMat(result);
    freeMat(result);
    return 0;
}
