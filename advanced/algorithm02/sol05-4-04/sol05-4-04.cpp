// sol05-4-04.cpp : 모의고사
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 각 수포자가 찍는 패턴
vector<int> pattern1 = { 1,2,3,4,5 };
vector<int> pattern2 = { 2,1,2,3,2,4,2,5 };
vector<int> pattern3 = { 3,3,1,1,2,2,4,4,5,5 };


vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> matchCnt(3);   // 크기 3의 벡터, 0으로 초기화

    // 실제 정답과 각 수포자 패턴 피교 맞힌개수 확인
    for (int i = 0; i < answers.size(); i++) {
        if (answers[i] == pattern1[i % pattern1.size()]) matchCnt[0]++;   // size 5

        if (answers[i] == pattern2[i % pattern2.size()]) matchCnt[1]++;   // size 8

        if (answers[i] == pattern3[i % pattern3.size()]) matchCnt[2]++;   // size 10        
    }

    // 가장 많은 수를 맞힌 수포자
    auto max_score = max_element(matchCnt.begin(), matchCnt.end());

    // max_score랑 같은 수포자 인덱스 찾기
    for (int i = 0; i < matchCnt.size(); i++) {
        if (matchCnt[i] == *max_score) {
            answer.push_back(i + 1);  // 인덱스를 사용X 수포자 번호를 사용
        }
    }

    return answer;
}

int main() {
    cout << "TEST CASE 1" << endl;

    vector<int> cases1 = { 1,2,3,4,5 };
    auto answer1 = solution(cases1);

    for (int num : answer1) {
        cout << num << ". ";
    }
    cout << endl;

    cout << "TEST CASE 2" << endl;

    vector<int> cases2 = { 1,3,2,4,2 };
    auto answer2 = solution(cases2);

    for (int num : answer2) {
        cout << num << ". ";
    }
    cout << endl;
}
