// IntStack.h 스택 자료구조 헤더파일

#ifndef ___IntStack  // 이름 지정에 큰 의미없음. 자기가 원하는 대로 할것 _INTSTACK_H_
#define ___IntStack

// 스택을 구현하는 구조체
typedef struct {
	int max;    // 스택 용량
	int ptr;	// 스택 포인터
	int* stk;	// 스택 첫 요소에 대한 포인터
} IntStack;

// 스택용 함수 선언

/*--- 스택 초기화 ---*/
// return type int는 실행 후 성공여부를 돌려받기 위해서 
// 리턴 -1 : 초기화실패
// 러턴 0 : 초기화성공
int Initialize(IntStack* st, int max);

/*--- 스택에 데이터 Push(푸시) ---*/
// 리턴 -1 : 푸시실패
// 리턴 0 : 푸시성공
int Push(IntStack* st, int x);

/*--- 스택에서 데이터 Pop(팝) ---*/
// 리턴 -1 : 팝실패
// 리턴 0 : 팝성공
// 팝 결과는 x로 돌려받음
int Pop(IntStack* st, int* x);

/*--- 스택에서 마지막 데이터 Peek(피크) ---*/
int Peek(const IntStack* st, int* x);

/*--- 스택 비우기 ---*/
void Clear(IntStack* st);

/*--- 스택 최대용량 ---*/
int Capacity(const IntStack* st);

/*--- 스택 데이터 개수 ---*/
int Size(const IntStack* st);

/*--- 스택 빈 여부확인 ---*/
int IsEmpty(const IntStack* st);

/*--- 스택 만실 여부확인 ---*/
int IsFull(const IntStack* st);

/*--- 스택 검색 ---*/
int Search(const IntStack* st, int x);

/*--- 스택 모든 데이터 출력 ---*/
int Print(const IntStack* st);

/*--- 스택 종료 ---*/
void Terminate(IntStack* st);

#endif
