#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* generateArray(int);
void bubbleSort(int *, int );
void insertionSort(int *, int );
void printArray(int*, int);
int binSearch(int , int* , int );

int main() {
    int size, toFind;
    puts("Enter size:");
    scanf("%d", &size);
    int* array = generateArray(size);
    puts("Initial array");
    printArray(array,size);
    puts("bubble sort");
    bubbleSort(array,size);
    printArray(array,size);
    puts("insertion sort");
    insertionSort(array,size);
    printArray(array,size);
    puts("Enter the number to find");
    scanf("%d", &toFind);
    printf("%d",binSearch(toFind,array,size));
    printf("\n");
//    memset(array, 0, sizeof(int)*size);
    free(array);
    printArray(array,size);
    return 0;
}

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
    printf("\n");
}

void bubbleSort(int *mas, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(mas[j] < mas[j+1]) {
                int tmp = mas[j];
                mas[j] = mas[j+1];
                mas[j+1] = tmp;
            }
        }
    }
}

void insertionSort(int* arr, int size){
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int binSearch(int a, int* arr, int n)
{
    int low, high, middle;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (a < arr[middle])
            high = middle - 1;
        else if (a > arr[middle])
            low = middle + 1;
        else
            return 0;
    }
    return -1;
}