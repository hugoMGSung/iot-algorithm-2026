// pointer05 - 구조체와 포인터

#include <stdio.h>

typedef struct {
	char name[20];
	int age;
} Person;

int main(void) {
	Person p1 = { .name = "Hugo", .age = 50 };
	Person* ptr = &p1;

	printf("이름 : %s\n", ptr->name);  // == *(ptr).name
	printf("나이 : %d\n", ptr->age);

	return 0;
}

// ptr->name 은 *(ptr).name 와 동일
// 구조체와 포인터는 함께 사용되는 경우가 매우 많음
// 임베디드/OS/네트워크 등에서 필수