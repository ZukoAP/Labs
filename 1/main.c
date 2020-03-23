#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct vector {
    void *value;
    int count;
    int elementSize;
    void *defaultValue;
};

void setValue(struct vector *vect, int index, void *value) {
    void *p = (vect->value + index * (vect->elementSize));
    memcpy(p, value, vect->elementSize);
}

struct vector *create(int count, int elementSize, void *defaultValue) {
    if (defaultValue == NULL) {
        defaultValue = malloc(elementSize * sizeof(char));
        *(float *) defaultValue = 0.0;
    }
    struct vector *vect = malloc(sizeof(struct vector));
    vect->value = malloc(count * elementSize * sizeof(char));
    vect->defaultValue = defaultValue;
    vect->count = count;
    vect->elementSize = elementSize;
    for (int i = 0; i < count; i++) {
        setValue(vect, i, defaultValue);
    }
    return vect;
}


void *getValue(struct vector *vect, int index) {
    return ((char *) vect->value + index * (vect->elementSize));
}

struct vector *addVect(struct vector *vect1, struct vector *vect2) {
    if (vect1->count != vect2->count) {
        printf("ERROR! Can't sum vectors with different dimension sizes\n");
        return NULL;
    }
    int dSize = vect1->count;
    struct vector *resVect = create(dSize, vect1->elementSize, vect1->defaultValue);
    for (int i = 0; i < dSize; i++) {
        float p = *(float *) getValue(vect1, i) + *(float *) getValue(vect2, i);
        setValue(resVect, i, &p);
    }
    free(vect1);
    free(vect2);
    return resVect;
}

void map(void *(*func)(void *), struct vector *vect) {
    for (int i = 0; i < vect->count; i++) {
        void *p = vect->value + i * (vect->elementSize);
        memcpy(p, (*func)(p), vect->elementSize);
    }
}

void *func1(void *val) {
    void *p = malloc(sizeof(float));
    *(float *) p = (*(float *) val * *(float *) val);
    return p;
}

void *func2(void *val) {
    void *p = malloc(sizeof(float));
    *(float *) p = *(float *) val + 1;
    return p;
}

void *func3(void *val) {
    void *p = malloc(sizeof(float));
    *(float *) p = *(float *) val / 2;
    return p;
}

/*void map(struct vector* vect){
    printf("What do you want to do with vector coordinates\n 1: square 2: +1 3: /2\n");
    int choice;
    scanf("%i",&choice);
    switch ( choice) {
        case 1:
            for (int i = 0; i < vect -> count; i++){
                float p = *(float *) getValue(vect, i) **(float *) getValue(vect, i);
                setValue(vect, i, &p);
            }
            break;
        case 2:
            for (int i = 0; i < vect -> count; i++){
                float p = *(float *) getValue(vect, i) +1;
                setValue(vect, i, &p);
            }
            break;
            case 3:
            for (int i = 0; i < vect -> count; i++){
                float p = *(float *) getValue(vect, i) /2;
                setValue(vect, i, &p);
            }
            break;
    }
    printf("Mapping result\n");
    for (int i = 0; i < vect->count; i++) {
        printf("%.2f ", *(float *) getValue(vect, i));
    }
}*/

void dotProd(struct vector *vect1, struct vector *vect2) {
    int dSize = vect1->count;
    float res = 0;
    for (int i = 0; i < dSize; i++) {
        float p = *(float *) getValue(vect1, i) * *(float *) getValue(vect2, i);
        res = res + p;
        printf("res: %.2f ", res);
    }
    printf("\nResult of dot product\n");
    printf("%.2f", res);
}

int main() {
    int dimSize = 0;
    printf("Enter dimension size\n");
    scanf("%d", &dimSize);
    printf("Creating vector\n");
    struct vector *vect = create(dimSize, sizeof(float), 0);
    float a = 0, b = 0;
    printf("Setting values\n");
    printf("Enter %i coordinates\n", dimSize);
    for (int i = 0; i < dimSize; i++) {
        scanf("%f", &a);
        setValue(vect, i, &a);
    }
    printf("Getting values\n");
    for (int i = 0; i < dimSize; i++) {
        printf("%.2f ", *(float *) getValue(vect, i));
    }

    printf("\nCreating other vector and trying to make dot product and add them together\n");
    printf("Enter %i coordinates of second vector\n", dimSize);
    struct vector *dif = create(dimSize, sizeof(float), 0);
    for (int i = 0; i < dimSize; i++) {
        scanf("%f", &b);
        setValue(dif, i, &b);
    }

    if (vect->count != dif->count) {
        printf("ERROR! Can't make dot product of vectors with different dimension sizes\n");
    } else {
        printf("Calculating dot product\n");
        dotProd(vect, dif);
    }
    printf("\nmapping\n");

    printf("What do you want to do with vector coordinates\n 1: square 2: +1 3: /2\n");
    int choice;
    scanf("%i", &choice);
    switch (choice) {
        case 1:
            map(func1, vect);
            break;
        case 2:
            map(func2, vect);
            break;
        case 3:
            map(func3, vect);
            break;
    }
    printf("Mapping result\n");
    for (int i = 0; i < vect->count; i++) {
        printf("%.2f ", *(float *) getValue(vect, i));
    }


    printf("\nAdding\n");
    vect = addVect(vect, dif);
    printf("Getting result\n");
    for (int i = 0; i < dimSize; i++) {
        printf("%.2f ", *(float *) getValue(vect, i));
    }
    free(vect);
    free(dif);
    return 0;
}