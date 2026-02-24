// IntQueue 구현 파일

#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

/*--- 큐 초기화 ---*/
// 파라미터 IntQueue &(주소), 최대크기
// 리턴값 -1(오류), 0(성공)
int Initialize(IntQueue* qu, int max) {
	qu->num = qu->front = qu->rear = 0;	

	if ( ( qu->que = calloc(max, sizeof(int)) ) == NULL ) { // 동적배열할당 오류면
		qu->max = 0;
		return -1; 
	}
	qu->max = max;
	return 0;
}

/*--- 큐에 데이터 인큐 ---*/
// 파라미터 IntQueue 주소, 들어갈 값
// 리턴값 -1(오류), 0(성공)
int Enque(IntQueue* qu, int x) {
	if (qu->num >= qu->max) { // 큐 Full
		return -1;
	}
	else {
		qu->num++;  // 데이터가 한건 증가
		qu->que[qu->rear] = x; // 큐 마지막에 추가
		qu->rear++;  // rear 1증가

		if (qu->rear == qu->max) {
			qu->rear = 0;  // 큐의 리어가 배열의 마지막까지 다 찼으면
		}

		return 0;
	}
}

/*--- 큐에 데이터 디큐 ---*/
// 파라미터 IntQueue 주소, 디큐로 가져올 값
// 리턴값 -1(오류), 0(성공)
int Deque(IntQueue* qu, int* x) {
	if (qu->num <= 0) {
		return -1;
	}
	else {
		qu->num--;  // 큐에서 데이터가 하나빠질꺼니까
		*x = qu->que[qu->front]; 
		qu->front++;

		if (qu->front == qu->max) { // deque를 계속해서 배열 마지막까지 도달
			qu->front = 0;
		}
		return 0;
	}
}

/*--- 큐에서 데이터 피크 ---*/
// 파라미터 IntQueue 주소(변경불가), 확인할 값
// 리턴값 -1(오류), 0(성공)
int Peek(const IntQueue* qu, int* x) {
	if (qu->num <= 0) {
		return -1;
	}

	*x = qu->que[qu->front];
	return 0;
}

/*--- 큐 클리어 ---*/
// 파라미터 전부삭제할 큐
// 리턴 없음
void Clear(IntQueue* qu) {
	qu->num = qu->front = qu->rear = 0;
}

/*--- 큐 최대용량 ---*/
// 파라미터 확인할 큐
// 리턴값 0~max
int Capacity(const IntQueue* qu) {
	return qu->max;
}

/*--- 큐에 저장된 데이터 수 ---*/
// 파라미터 확인할 큐
// 리턴값 0~num
int Size(const IntQueue* qu) {
	return qu->num;
}

/*--- 큐 종료 ---*/
void Terminate(IntQueue* qu) {
	if (qu->que != NULL) {
		free(qu->que);
	}
	qu->max = qu->num = qu->front = qu->rear = 0;
}

/*--- 큐가 비어있는가? ---*/
int IsEmpty(const IntQueue* qu) {
	return qu->num <= 0;
}

/*--- 큐가 가득찼는가? ---*/
int IsFull(const IntQueue* qu) {
	return qu->num >= qu->max;
}

/*--- 큐 출력 ---*/
void Print(const IntQueue* qu) {
	for (int i = 0; i < qu->num; i++) {
		// (qu->front + i) % qu->max -> rear가 front보다 작을 수 있음.
		printf("%d ", qu->que[(qu->front + i) % qu->max]);
	}
	printf("\n");
}

/*--- 큐 검색 ---*/
int Search(const IntQueue* qu, int x) {
	for (int i = 0; i < qu->num; i++) {
		int idx = (qu->front + i) % qu->max;
		if (qu->que[idx] == x) {
			return idx;
		}
	}

	return -1;
}