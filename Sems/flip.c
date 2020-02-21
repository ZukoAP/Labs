#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** createMatrix(int rows, int columns);
void showMatrix(int** mat,int rows, int cols);
void invertRow(int** mat,int rowNum, int cols);
void invertColumn(int** mat,int colNum, int rows);


int main() {
    int rows, cols, balance = 0;
    long sum=0;
    scanf("%d %d", &rows, &cols);
    int** mat = createMatrix(rows,cols);
    for (int i = 0; i < rows; ++i) {
        if (mat[i][0] == 0){
            invertRow(mat,i,cols);
        }
    }
    for (int i = 1; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            balance = (mat[j][i] == 0) ? balance-1 : balance+1;
        }
        if (balance < 0)
            invertColumn(mat,i,rows);
        balance = 0;
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if(mat[row][col]==1)
                sum += (long) powl(2,cols-col-1);
        }
    }
    printf("%ld",sum);
    return 0;
}

int** createMatrix(int rows, int columns){
    int** mat = (int**) malloc(sizeof(int*)*rows);
    for (int row = 0; row < rows; ++row) {
        mat[row] = (int*) malloc(sizeof(int)*columns);
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            scanf("%d", &mat[row][col]);
        }
    }
    return mat;
}

void showMatrix(int** mat,int rows,int cols){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            printf("%d ",mat[row][col]);
        }
        printf("\n");
    }
}

void invertRow(int** mat,int rowNum, int cols){
    for (int col = 0; col < cols; ++col) {
//        mat[rowNum][col] = (mat[rowNum][col] == 0) ? 1 : 0;
        mat[rowNum][col] = 1 - mat[rowNum][col];
    }
}

void invertColumn(int** mat,int colNum, int rows){
    for (int row = 0; row < rows; ++row) {
//        mat[row][colNum] = (mat[row][colNum] == 0) ? 1 : 0;
        mat[row][colNum] = 1 - mat[row][colNum];
    }
}