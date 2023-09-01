#include "symnmf.h"

int main(int argc, char** argv) {
    int rows, cols;
    MAT* matrix = readCSVtoMatrix(argv[2]);

    if (argv[1] == "sym"){printMat(createSymMat(matrix));}
    else if (argv[1] == "ddg"){printMat(createDdgMat(matrix));}
    else if (argv[1] == "norm"){printMat(createNsmMat(matrix));}
    else{
        printf("An Error has Occured");
        exit(1);
    }

    return 0;
}