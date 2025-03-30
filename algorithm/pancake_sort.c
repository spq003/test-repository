#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 5

void print_arr();

void swap(int *arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


/* flip_index에 대한 loop 수
 * 1, 2 = 1번
 * 3, 4 = 2번
 * 5, 6 = 3번 ... */
int* flip(int *arr, int flip_index){
    if(flip_index == 0) return arr;

    int loops = (flip_index+1)/2;

    int end = flip_index;
    for(int i = 0; i < loops; i++){
        printf("swap %d %d\n", i, end);
        swap(arr, i, end--);
    }
}

int main(){
    srand(time(NULL));

    int* pancakes = malloc(sizeof(int) * ARR_SIZE);
    for(int i = 0; i < ARR_SIZE; i++){
        pancakes[i] = i;
    }
    print_arr(pancakes);

    flip(pancakes, 1);
    print_arr(pancakes);

    return 0;
}

void print_arr(int* arr){
    for(int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}