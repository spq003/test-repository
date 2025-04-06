#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print_arr(char** arr, int size);
void input_board(char** arr, int size);
void free_arr(char** arr, int size);
char** create_arr(int size);

// https://nypc.github.io/2016/spinandslide.html
/* test case

7
2
.......
.......
...A...
...B...
..ACA..
..BBB..
.AAAAA.

*/

void spin(char** arr, int size) {
	char** tmp = create_arr(size); //회전용 임시 배열 할당

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp[j][size - i - 1] = arr[i][j];
		}
	}

	//기존 배열에 값 입력
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			arr[i][j] = tmp[i][j];
		}
	}

	free_arr(tmp, size); //임시 배열 해제
}

void pull(char** arr, int i, int j) {
	for (; j >= 1; j--) {
		arr[j][i] = arr[j - 1][i];
	}
	arr[0][i] = '.';
}

void slide(char** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 1; j--) {
			for (int k = 0; k < size; k++) {
				if (arr[j][i] == '.') {
					pull(arr, i, j);
				}
				else break;
			}
		}
	}
}

void spin_and_slide(char** arr, int size) {
	spin(arr, size);
	slide(arr, size);
}

int main() {
	int board_size, spin_count;
	scanf("%d", &board_size);
	scanf("%d", &spin_count);


	char** game_board = create_arr(board_size);
	input_board(game_board, board_size);


	for (int i = 0; i < spin_count; i++)
		spin_and_slide(game_board, board_size);


	print_arr(game_board, board_size);
	free_arr(game_board, board_size);
	return 0;
}


void free_arr(char** arr, int size) {
	for (int i = 0; i < size; i++) {
		free(arr[i]);
	}
	free(arr);
}

char** create_arr(int size) {
	char** arr = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; i++) {
		arr[i] = (char*)malloc(sizeof(char) * size);
	}
	return arr;
}

void input_board(char** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			scanf(" %c", &arr[i][j]);
		}
	}
	printf("\n");
}

void print_arr(char** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}