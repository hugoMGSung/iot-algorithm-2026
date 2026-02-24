// app05 - 재귀 알고리즘 비재귀로 변경

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "IntStack.h"

/*--- 재귀함수 호출부분 제거 ---*/
void recur(int n) {
	IntStack stk;    // 스택추가
	Initialize(&stk, 100);

Top:  // 
	if (n > 0) {
		//recur(n - 1); // 머리재귀 제거
		Push(&stk, n);    // n값을 스택에 푸시
		n = n - 1;
		goto Top;
	}

	if (!IsEmpty(&stk)) { // 스택이 비어있지 않으면
		Pop(&stk, &n);   // 임시 저장한 n값 팝
		printf("%d\n", n);

		//recur(n - 2); // 꼬리재귀 제거
		n = n - 2;
		goto Top;
	}

	Terminate(&stk);
}

int main(void) {
	int x;

	while (1) {
		printf("정수 입력 > "); scanf("%d", &x);

		if (x <= 0) break;

		recur(x);
	}

	return 0;
}