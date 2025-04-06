#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//하노이 탑 이동하기 https://www.acmicpc.net/problem/11729

/* 탑을 이동시키는 방법??
* 
* 맨 밑의 원판을 제외한 모든 원판을 가운데로 이동시킨다. (recursion)
* 왼쪽에 있는 가장 큰 원판을 오른쪽으로 이동시킨다.
* 가운데 쌓인 원판을 우측으로 옮긴다. (recursion)
* 
* n-1개의 원판을 어떻게 가운데로 이동시키는가??
* >>>> Recursion Fairy가 옮겨줌...
*/

void hanoi(int size, int left, int center, int right) {
	if (size <= 0) return;
	hanoi(size - 1, left, right, center);
	printf("%d %d\n", left, right); //맨 위의 원판을 left에서 right로 이동!
	hanoi(size - 1, center, left, right);
}

int hanoi_count(int size, int left, int center, int right) {
	static int i;
	if (size <= 0) return i;
	hanoi_count(size - 1, left, right, center);
	i++;
	hanoi_count(size - 1, center, left, right);
	return i;
}


int main() {
	int size;
	scanf("%d", &size);

	int left = 1;
	int center = 2;
	int right = 3;

	int count;
	count = hanoi_count(size, left, center, right);
	printf("%d\n", count);
	hanoi(size, left, center, right);
	return 0;
}