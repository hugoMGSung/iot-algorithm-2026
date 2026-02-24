// IntQueue 헤더 파일
#ifndef ___IntQueue
#define ___IntQueue

typedef struct {
	int max;		// 큐 최대크기
	int num;		// 큐 현재 요소 개수
	int front;	// 큐 프런트
	int rear;	// 큐 리어
	int* que;   // 실제 큐데이터의 맨 앞요소의 포인터
} IntQueue;

/*--- 큐 초기화 ---*/
// 파라미터 IntQueue &(주소), 최대크기
// 리턴값 -1(오류), 0(성공)
int Initialize(IntQueue* qu, int max);

/*--- 큐에 데이터 인큐 ---*/
// 파라미터 IntQueue 주소, 들어갈 값
// 리턴값 -1(오류), 0(성공)
int Enque(IntQueue* qu, int x);

/*--- 큐에 데이터 디큐 ---*/
// 파라미터 IntQueue 주소, 디큐로 가져올 값
// 리턴값 -1(오류), 0(성공)
int Deque(IntQueue* qu, int* x);

/*--- 큐에서 데이터 피크 ---*/
// 파라미터 IntQueue 주소(변경불가), 확인할 값
// 리턴값 -1(오류), 0(성공)
int Peek(const IntQueue* qu, int* x);

/*--- 큐 클리어 ---*/
// 파라미터 전부삭제할 큐
// 리턴 없음
void Clear(IntQueue* qu);

/*--- 큐 최대용량 ---*/
// 파라미터 확인할 큐
// 리턴값 0~max
int Capacity(const IntQueue* qu);

/*--- 큐에 저장된 데이터 수 ---*/
// 파라미터 확인할 큐
// 리턴값 0~num
int Size(const IntQueue* qu);

/*--- 큐가 비어있는가? ---*/
int IsEmpty(const IntQueue* qu);

/*--- 큐가 가득찼는가? ---*/
int IsFull(const IntQueue* qu);

/*--- 큐 검색 ---*/
int Search(const IntQueue* qu, int x);

/*--- 큐 출력 ---*/
void Print(const IntQueue* qu);

/*--- 큐 종료 ---*/
void Terminate(IntQueue* qu);

#endif