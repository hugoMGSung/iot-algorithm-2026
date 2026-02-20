// p13. 알고리즘이란?
// 세 정수를 입력, 최대값 구하기

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int a, b, c; 
	int max = 0;

	printf("세 정수 중 최대값을 리턴.\n");

	printf("a > "); scanf("%d", &a);
	printf("b > "); scanf("%d", &b);
	printf("c > "); scanf("%d", &c);

	// 1, 5, 3

	max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}

	printf("최대값은 %d\n", max);

	return 0;
}