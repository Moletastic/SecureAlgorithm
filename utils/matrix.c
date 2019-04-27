#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void showMatrix(int** matrix, int rows, int columns){
    short i,j;
    for(i = 0; i < rows ; i++){
        for(j = 0; j < columns; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int rowSum(int* row, int length){
    short i, sum = 0;
    for(i = 0; i < length; i++){
        sum += row[i];
    }
    return sum;
}