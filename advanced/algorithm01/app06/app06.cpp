// app06.cpp : 코드 구현 노하우
//

#include <iostream>
#include <vector>

using namespace std;

// 조기반환
// 주어진 수량과 가격에 따라 총 가격을 계산하는 함수
double total_price(int quantity, double price) {
    double total = quantity * price;  // 총 금액 계산
    
    if (total > 100) { // total이 100보다 크면
        return total * 0.9;    // 조기반환
    }

    return total;  // 최종반환
}

// 보호구문
// 벡터 값을 모두 더해서 N으로 나누 값 반환
double get_avg(const vector<int>& arr, int N) {
    // 벡터가 비어있는 예외처리
    if (arr.empty()) {
        return -1;   // -1 리턴 종료
    }

    if (N == 0) { // Divide by Zero 예외처리
        return -1;
    }

    int sum = 0;
    for (int num : arr) {
        sum += num;
    }

    return sum / N;
}

int main()
{
    cout << "코드 구현 노하우\n===================" << endl;
    cout << endl;

    // 조기반환
    cout << "조기반환" << endl;
    cout << total_price(4, 50) << endl;  // 조기반환문 만나서 180 출력

    // 보호구문
    cout << "보호구문" << endl;
    vector<int> arr = { 1,2,3,4,5 };
    cout << "평균 = " << get_avg(arr, 5) << endl;


    return 0;
}
