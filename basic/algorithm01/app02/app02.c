// p22. 중앙값

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 3, 2, 1 => 2
// 3, 1, 5 => 3
// 3, 1, 2 => 2
// 2, 3, 1 => 2
int median3(int a, int b, int c) {
	if (a >= b) {
		if (b >= c) {
			return b;
		}
		else if (a <= c) {
			return a;
		}
		else {
			return c;
		}
	}
	else if (a > c) {
		return a;  // b가 제일크고, a가 두번째니까 
	}
	else if (b > c) {
		return c;
	}
	else {
		return b;
	}
}

int main(void) {
	int a, b, c;

	printf("세 정수 입력\n");
	printf("a 값 > "); scanf("%d", &a);
	printf("b 값 > "); scanf("%d", &b);
	printf("c 값 > "); scanf("%d", &c);

	printf("중앙값은 %d\n", median3(a, b, c));

	return 0;
}