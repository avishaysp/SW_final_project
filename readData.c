#include "readData.h"

MAT*  readCSVtoMatrix(const char* filename) {
    char dummy;  
    int rowCount = 0;
    int colCount = 0;
    char* line;
    MAT* matrix;
    int row;
    int lineLength;
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("An Error Has Occurred\n");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);     
    while (fread(&dummy, 1, 1, file) && dummy != '\n') {
        if (dummy == ','){
            colCount++;
        }
    }
    colCount += 1;
    lineLength = 15 * colCount;
    line = (char*)malloc(lineLength * sizeof(char));

    fseek(file, 0, SEEK_SET); 
     
    while (fgets(line, lineLength, file)) {
        if (strlen(line) <= 1) {
            break; 
        }
        if (rowCount == 0) {
            char* token = strtok(line, ",");
            while (token) {
                token = strtok(NULL, ",");
            }
        }
        rowCount++;
    }

    printf("%d %d\n", rowCount, colCount);

    matrix = initMat(rowCount, colCount);

    fseek(file, 0, SEEK_SET);
    row = 0;
    while (fgets(line, colCount, file) && row < rowCount) {
        char* token = strtok(line, ",");
        int col = 0;
        while (token) {
            matrix->vals[row][col] = atof(token);
            col++;
            token = strtok(NULL, ",");
        }
        row++;
    }

    free(line);
    fclose(file);

    return matrix;
}

