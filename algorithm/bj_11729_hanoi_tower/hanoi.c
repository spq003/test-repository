#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//�ϳ��� ž �̵��ϱ� https://www.acmicpc.net/problem/11729

/* ž�� �̵���Ű�� ���??
* 
* �� ���� ������ ������ ��� ������ ����� �̵���Ų��. (recursion)
* ���ʿ� �ִ� ���� ū ������ ���������� �̵���Ų��.
* ��� ���� ������ �������� �ű��. (recursion)
* 
* n-1���� ������ ��� ����� �̵���Ű�°�??
* >>>> Recursion Fairy�� �Ű���...
*/

void hanoi(int size, int left, int center, int right) {
	if (size <= 0) return;
	hanoi(size - 1, left, right, center);
	printf("%d %d\n", left, right); //�� ���� ������ left���� right�� �̵�!
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