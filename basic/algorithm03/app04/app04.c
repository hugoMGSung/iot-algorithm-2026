// app04 - 재귀 알고리즘 분석
// 하향식 방법 분석

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 함수호출횟수 카운터 변수
int callCnt = 0;

/*--- 재귀함수 recur 선언과 정의 ---*/
void recur(int n) {
	callCnt++;  // 함수호출회수 증가

	if (n > 0) { // 종료 조건 n이 0보다 크다. 0이하로 떨어지면 종료된다.
		recur(n - 1);  // 1. 1 - 1 이 될때까지 3번 반복
		printf("%d\n", n); // 2. 1번 반복이 끝나야 출력이 시작
		recur(n - 2); // 3. 2번 출력후 재귀호출. 0이하로 떨어지면 재귀종료. 
	}
}

int main(void) {
	int x;

	while (1) {
		printf("정수 입력 > "); scanf("%d", &x);

		if (x <= 0) break;

		callCnt = 0;  // 입력받을때마다 초기화
		recur(x);
		printf("함수 총 호출회수 : %d\n\n", callCnt);
	}

	return 0;
}