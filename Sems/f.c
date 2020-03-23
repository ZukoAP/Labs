#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int* generateArray(int size){
    int* arr = (int*) malloc(sizeof(int) * size);
    srand(time(0));
    for( int i = 0 ; i < size ; i++ ) {
        arr[i] = rand() % 10;
    }
    return arr;
}

void printArray(int* arr, int size){
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
}


int* delete(int* arr, int* size,int div){
    int* pBad = arr;
    int* pNice = arr;
    int k=0;
    for (int i = 0; i < *size; ++i) {
        if ((arr[i]%div) != 0){
            *(pNice)=*pBad;
            pNice+=1;
            k+=1;
        };
        pBad+= 1;
    }
    *size = k;
    printf("size: %d \n", *size);
    arr = (int*) realloc(arr,k * sizeof(int));
    return arr;
}

int main() {
    int size;
    puts("Enter size:");
    scanf("\n%d", &size);
    int *array = generateArray(size);
    puts("Initial array");
    printArray(array, size);
    int div;
    printf("\nSet divider\n");
    scanf("%i",&div);
    delete(array,&size,div);
    printArray(array, size);
    if(!size)
        puts("No such numbers");
    return 0;
}