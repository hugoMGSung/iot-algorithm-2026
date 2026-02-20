// pointer 02 - 함수와 포인터

#include <stdio.h>

void change(int*);

int main(void) {
	int num = 10;

	change(&num);
	printf("변경된 num : %d\n", num);

	return 0;
}

void change(int* p) {
	*p = 300;  // 원래있던 10이 300으로 변경
}

// 일반 변수 전달 복사
// 포인터의 전달 `원본 조작`
// 임베디드에서 매우 중요