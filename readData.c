#include "readData.h"

MAT*  readCSVtoMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file.\n");
        return NULL;
    }

    // Determine the length of the first line
    fseek(file, 0, SEEK_SET);     // Move to beginning of file
    char dummy;  // For reading the file character by character
    int lineLength = 0;
    while (fread(&dummy, 1, 1, file) && dummy != '\n') {
        lineLength++;
    }
    lineLength += 2;  // Adjust for potential '\r' (in case of CRLF line endings) and null terminator
    char* line = (char*)malloc(lineLength * sizeof(char));

    int rowCount = 0;
    int colCount = 0;

    // Count rows and columns
    fseek(file, 0, SEEK_SET);  // Move back to the start of the file
    while (fgets(line, lineLength, file)) {
        if (strlen(line) <= 1) {
            break; // Empty line or last line
        }
        if (rowCount == 0) {
            // Count number of columns based on number of commas
            char* token = strtok(line, ",");
            while (token) {
                colCount++;
                token = strtok(NULL, ",");
            }
        }
        rowCount++;
    }

    MAT* matrix = initMat(rowCount, colCount);

    // Rewind the file to start and read the values into the matrix
    fseek(file, 0, SEEK_SET);
    int row = 0;
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

