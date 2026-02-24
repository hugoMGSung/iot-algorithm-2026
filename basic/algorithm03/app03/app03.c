// app03 - 팩토리얼 비재귀적 구현

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

unsigned long long factorial_iter(int n);

int main(void) {
	int x;
	unsigned long long result = 0;
	puts("팩토리얼 비재귀호출");

	while (1) {
		printf("정수 입력 > "); scanf("%d", &x);
		if (x <= 0) break;

		result = factorial_iter(x); 

		printf("%d! = %llu\n", x, result);
	}

	return 0;
}

// 재귀를 사용하지 않는 팩토리얼 함수
unsigned long long factorial_iter(int n) {
	unsigned long long result = 1;

	for (int i = 2; i <= n; i++) {
		result *= (unsigned long long)i;  // n * factorial(n - 1)
	}

	return result;
}