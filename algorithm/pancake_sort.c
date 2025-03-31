#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10

void print_arr();

void swap(int* arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


/* flip_index에 대한 loop 수
 * 1, 2 = 1번
 * 3, 4 = 2번
 * 5, 6 = 3번 ... i+1을 2로 나누기!*/
int* flip(int* arr, int flip_index) {
    if (flip_index == 0) return arr;

    int loops = (flip_index + 1) / 2;

    int end = flip_index;
    for (int i = 0; i < loops; i++)
        swap(arr, i, end--);
    return arr;
}

int find_max_index(int* arr, int size) {
    int max_index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > arr[max_index])
            max_index = i;
    }
    return max_index;
}

int* pancake_sort(int* pancakes, int size) {
    for (int now = size; now > 1; now--) {
        int max_index = find_max_index(pancakes, now);
        if (max_index != 0)
            flip(pancakes, max_index);
        flip(pancakes, now-1);
    }
}

// test case
// 4 5 9 1 2 3 8 6 7
int main() {
    srand(time(NULL));

    int* pancakes = malloc(sizeof(int) * ARR_SIZE);
    if (pancakes == NULL) return -1; 
    for (int i = 0; i < ARR_SIZE; i++) {
        //scanf("%d", &pancakes[i]);
        pancakes[i] = rand() % 99;
    }

    print_arr(pancakes);
    pancake_sort(pancakes, ARR_SIZE);
    print_arr(pancakes);

    return 0;
}

void print_arr(int* arr) {
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}