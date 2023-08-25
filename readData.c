#include "readData.h"

MAT* createDataMatrix(void){
    int i, j;
    int numberOfVectors = 0, vectorsLength = 0;
    MAT* mat;
    VECTOR* input_vec = getInput(&numberOfVectors, &vectorsLength);
    CORD* c;
    VECTOR* head = input_vec;
    VECTOR* curr_vec = head;
    int num = numberOfVectors;
    int length = vectorsLength;
    mat = initMat(num, length);
    for(i = 0; i < num; i++){
        c = curr_vec -> cords;
        for(j = 0; j < length; j++){
            mat->vals[i][j] = c -> value;
            if (j < length - 1) {
                c = c -> next;
            }
        }
        curr_vec = curr_vec -> next;
    }
    deleteList(head);
    return mat;
}


void deleteCords(CORD* head) {
    if (head != NULL) {
        deleteCords(head->next);
        free(head);
    }
}

void deleteList(VECTOR* vec){
    if (vec != NULL) {
        deleteList(vec->next);
        deleteCords(vec->cords);
        free(vec);
    }
}

VECTOR* getInput(int* numOfVectors, int* vectorsLength)
{
    VECTOR *head_vec, *curr_vec;
    CORD *head_cord, *curr_cord;
    int num = 0, length = 1;
    double n;
    char c;

    head_cord = (CORD*)malloc(sizeof(CORD));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = (VECTOR*)malloc(sizeof(VECTOR));
    curr_vec = head_vec;
    curr_vec->next = NULL;

    while (scanf("%lf%c", &n, &c) == 2) {
        if (c == '\n') {
            num++;
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = (VECTOR*)malloc(sizeof(VECTOR));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = (CORD*)malloc(sizeof(CORD));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }
        if (num == 0) {
            length++;
        }
        curr_cord->value = n;
        curr_cord->next = (CORD*)malloc(sizeof(CORD));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    *numOfVectors = num;
    *vectorsLength = length;
    return head_vec;
}


