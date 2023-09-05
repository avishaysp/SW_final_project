#include "symnmf.h"

int main(int argc, char** argv) {
    MAT* matrix = readCSVtoMatrix(argv[2]);
    if (argc > 3){
        exit(1);
    }

    if (strcmp(argv[1], "sym") == 0){
        printMat(createSymMat(matrix));
    }

    else if (strcmp(argv[1], "ddg") == 0){
        printMat(createDdgMat(matrix));
    }

    else if (strcmp(argv[1], "norm") == 0){
        printMat(createNsmMat(matrix));
    }

    else{
        printf("An Error has Occured");
        exit(1);
    }

    return 0;
}
