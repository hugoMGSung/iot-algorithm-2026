// app06 - goto문 사용 예제
// goto문은 되도록 사용하지 말것! 

#include <stdio.h>

int main(void) {
	int i = 0;

start: // 라벨, 앵커(돛)
	printf("i = %d\n", i);
	i++;

	if (i < 5) goto start; // start 라벨로 점프!

	printf("끝!\n");
	return 0;
}