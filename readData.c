#include "readData.h"

MAT*  readCSVtoMatrix(const char* filename) {
    char dummy;  
    int rowCount = 0;
    int colCount = 0;
    int lineLength = 0;
    char* line;
    MAT* matrix;
    int row;
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("An Error Has Occurred\n");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);     
    while (fread(&dummy, 1, 1, file) && dummy != '\n') {
        lineLength++;
    }
    lineLength += 2; 
    line = (char*)malloc(lineLength * sizeof(char));

    fseek(file, 0, SEEK_SET);  
    while (fgets(line, lineLength, file)) {
        if (strlen(line) <= 1) {
            break; 
        }
        if (rowCount == 0) {
            char* token = strtok(line, ",");
            while (token) {
                colCount++;
                token = strtok(NULL, ",");
            }
        }
        rowCount++;
    }

    matrix = initMat(rowCount, colCount);

    fseek(file, 0, SEEK_SET);
    row = 0;
    while (fgets(line, lineLength, file) && row < rowCount) {
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

