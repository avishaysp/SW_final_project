#include "readData.h"

static int maxCharsInRow(FILE *csvFile) {
    int maxChars = 0;
    int currentChars = 0;
    int c;

    if (csvFile == NULL) {
        printf("An Error Has Occurred\n");
        return -1;
    }

    rewind(csvFile);

    while ((c = fgetc(csvFile)) != EOF) {
        if (c != '\n' && c != '\r') {
            currentChars++;
        } else {
            if (currentChars > maxChars) {
                maxChars = currentChars;
            }
            currentChars = 0;
        }
    }

    if (currentChars > maxChars) {
        maxChars = currentChars;
    }

    rewind(csvFile);
    return maxChars;
}


MAT*  readCSVtoMatrix(const char* fileName) {
    char dummy;
    int rowCount = 0;
    int colCount = 0;
    char* line;
    MAT* matrix;
    int row;
    int maxLineLength;
    FILE* file;
    file = fopen(fileName, "r");
    maxLineLength = maxCharsInRow(file);
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
    line = (char*)malloc(maxLineLength * sizeof(char));

    fseek(file, 0, SEEK_SET);

    while (fgets(line, maxLineLength, file)) {
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

