#include "symnmf.h"

int main(int argc, char** argv) {
    MAT* matrix = readCSVtoMatrix(argv[2]);
    if (argc > 2){
        exit(1);
    }

    if (strcmp(argv[1], "sym")){printMat(createSymMat(matrix));}
    else if (strcmp(argv[1], "ddg")){printMat(createDdgMat(matrix));}
    else if (strcmp(argv[1], "norm")){printMat(createNsmMat(matrix));}
    else{
        printf("An Error has Occured");
        exit(1);
    }

    return 0;
}
