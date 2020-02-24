#include <stdio.h>
#include <stdlib.h>

struct vector
{
    int *coordinates;
};
void createVector(struct vector* newVector, int dimensionSize){
    newVector->coordinates = (int*) malloc(dimensionSize*sizeof(int));
    puts("Enter coordinates of the new vector");
    for(int currCoord=0; currCoord<dimensionSize; currCoord++){
        printf("e%d = ",currCoord+1);
    }

}

int main(){
    printf("Vector size: %llu \n", sizeof(struct date));
    puts("Put dimension size")
//    system ( "Pause" );
    return 0;
}