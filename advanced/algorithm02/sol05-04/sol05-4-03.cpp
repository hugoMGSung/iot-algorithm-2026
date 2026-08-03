// sol05-4-03.cpp 두 수를 뽑아서 더하기
//

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// 프로그래머스의 함수 프로토타입
vector<int> solution(vector<int> numbers) {
    set<int> sum;  // 두 수의 합을 저장할 변수

    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = i + 1; j < numbers.size(); ++j) {
            sum.insert(numbers[i] + numbers[j]);  // 중복 제거
        }
    }

    vector<int> answer(sum.begin(), sum.end());  // set -> vector
    return answer;
}

// 메인 함수로 테스트 케이스 실행결과 확인
int main() {
    cout << "TEST CASE 1" << endl;

    vector<int> cases1 = { 2,1,3,4,1 };
    auto answer1 = solution(cases1);

    for (int num : answer1) {
        cout << num << ". ";
    }
    cout << endl;

    cout << "TEST CASE 2" << endl;

    vector<int> cases2 = { 5,0,2,7 };
    auto answer2 = solution(cases2);

    for (int num : answer2) {
        cout << num << ". ";
    }
    cout << endl;

}
