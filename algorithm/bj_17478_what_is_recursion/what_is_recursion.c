#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ����Լ��� ������?? https://www.acmicpc.net/problem/17478

void print_tab(int i) {
	while (i > 0) {
		printf("____");
		i--;
	}
}

void what_is_recursion(int i, int max) {
	print_tab(i);
	printf("\"����Լ��� ������?\"\n");

	if (i == max) {
		print_tab(i);
		printf("\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n");
		print_tab(i);
		printf("��� �亯�Ͽ���.\n");
		return;
	}

	print_tab(i);
	printf("\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n");
	print_tab(i);
	printf("���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n");
	print_tab(i);
	printf("���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n");
	what_is_recursion(i+1, max);
	print_tab(i);
	printf("��� �亯�Ͽ���.\n");
}

int main() {
	int count;
	scanf("%d", &count);

	printf("��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n");
	what_is_recursion(0, count);
	return 0;
}