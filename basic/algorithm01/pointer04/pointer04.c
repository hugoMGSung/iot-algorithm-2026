// pointer04 - 이중 포인터

#include <stdio.h> 

// 변수를 전달해서 값 전환
void swap1(int* a, int* b) {
	int temp = *a;  // a가 가리키는 값을 할당
	*a = *b;
	*b = temp;
}

// 포인터변수를 전달해서 주소를 전환
void swap2(int** a, int** b) {
	int* temp = *a;  // a가 가리키는 주소를 할당
	*a = *b;
	*b = temp;
}

int main(void) {
	int x = 25, y = 52;

	printf("변수로 변경 전 x = %d, y = %d\n", x, y);
	swap1(&x, &y);
	printf("변수로 변경 후 x = %d, y = %d\n", x, y);

	int* px = &x;
	int* py = &y;

	printf("포인터변수로 변경 전 x = %d, y = %d, *px = %d, *py = %d\n", x, y, *px, *py);
	swap2(&px, &py);
	printf("포인터변수로 변경 후 x = %d, y = %d, *px = %d, *py = %d\n", x, y, *px, *py);

	return 0;
}

// int* 변수의 주소
// int** 포인터의 주소
// 포인터를 바꾸려면 이중 포인터 필요