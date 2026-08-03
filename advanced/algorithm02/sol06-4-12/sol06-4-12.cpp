// sol06-4-12.cpp : 주식 가격

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());  // 벡터 크기로 
    stack<int> st;  // 스택에는 prices의 인덱스를 push, pop

    for (int i = 0; i < prices.size(); i++) {
        // 다음 가격이 떨어졌으면
        while (!st.empty() && prices[st.top()] > prices[i]) {
            // 가격이 떨어졌으므로 이전 가격의 기간 계산
            answer[st.top()] = i - st.top(); // 
            st.pop();  // 더 큰값은 뺌
        }
        
        st.push(i);  // 0(1), 1(6), 2(9)  -> 0(1)  -> 0(1), 3(5)
    }

    while (!st.empty()) { // 스택이 다 빌때까지
        answer[st.top()] = prices.size() - st.top() - 1;  // size()는 1부터 시작, 인덱스는 0부터 시작 -1 추가
        st.pop();
    }

    return answer;
}

int main()
{
    cout << "주식가격\n";

    vector<int> cases1 = { 1, 2, 3, 2, 3 };  // 4, 3, 1, 1, 0
    auto result1 = solution(cases1);
    for (int num : result1) {
        cout << num << ". ";
    }
    cout << endl;

    vector<int> cases2 = { 1, 6, 9, 5 };  // 3, 2, 1, 0
    auto result2 = solution(cases2);
    for (int num : result2) {
        cout << num << ". ";
    }
    cout << endl;

    vector<int> cases3 = { 1, 6, 9, 5, 3, 2, 7 };   // 6, 2, 1, 1, 1, 1, 0
    auto result3 = solution(cases3);
    for (int num : result3) {
        cout << num << ". ";
    }
    cout << endl;
}
