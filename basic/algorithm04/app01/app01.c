// app01 - 메모이제이션
// 성능 향상 극대화 기법

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int callCnt = 0;
// 저장할 배열 선언
static char memo[128][8192];  // 128행 1024열 문자열. 길이가 1024이되는 문자열을 128개 보관
// 메모리 128kbyte를 할당해야함

/*--- 메모이제이션 recur함수 ---*/
void recur(int n) {
	callCnt++; 

	if (memo[n + 1][0] != '\0') {  // 상위값이 저장되어 있으면
		printf("%s", memo[n + 1]);   // 메모만 출력하면 끝
	}
	else {
		if (n > 0) { // 재귀호출
			recur(n - 1);
			printf("%d\n", n);
			recur(n - 2);
			// 메모리에 저장
			// printf("%s%d\n%s", memo[n], n, memo[n - 1]); 와 비교
			sprintf(memo[n + 1], "%s%d\n%s", memo[n], n, memo[n - 1]);
		}
		else {
			// memo[0] recur(-1) 저장, memo[1] recur(0) 저장
			strcpy(memo[n + 1], "");  
		}
	}
}

int main(void) {
	int x;

	while (1) {
		printf("정수 입력 > "); scanf("%d", &x);

		if (x <= 0) break;

		callCnt = 0;
		recur(x);
		printf("함수 총 호출회수 : %d\n\n", callCnt);
	}

	return 0;
}