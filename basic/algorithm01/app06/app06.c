// app06 - 이전 소수계산에서 나누기 횟수가 78022번
// 합성수로는 나눌 필요가 없으므로 나누기를 줄일수 있음
// 이 소스로 실행하면 나누기 횟수가 14622번으로 줄었음
// 다음 소스를 실행하면 나누기 회수를 3774번으로 줄일 수 있음

// 메모리 사용량 : 2000 + 20 = 2020byte = 2Kbyte

#include <stdio.h>

int main(void) {
	int prime[500];			// 이전 계산한 소수 저장하는 배열   2000byte
	int prime_cnt = 0;			// 소수의 개수 
	unsigned long counter = 0;

	prime[prime_cnt++] = 2;       // 2는 소수

	for (int n = 3; n <= 1000; n += 2) {
		int i;
		for (i = 1; i < prime_cnt; i++) {
			counter++;

			if (n % prime[i] == 0) {  // 소수아님
				break;
			}
		}
		if (prime_cnt == i) {
			prime[prime_cnt++] = n;  // 마지막까지 나누어지지 않으면 소수배열 저장
		}
	}

	// 출력은 따로
	for (int i = 0; i < prime_cnt; i++) {
		printf("%d\n", prime[i]);
	}

	printf("1~1000사이 소수 개수 : %u\n", prime_cnt);
	printf("나눗셈 실행 횟수 : %lu\n", counter);
}