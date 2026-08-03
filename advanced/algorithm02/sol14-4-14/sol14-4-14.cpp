// sol14-4-14.cpp : 표 편집
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// n 배열 크기, k 행의 위치, cmd 명령어 벡터
string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    stack<int> deleted;  // 삭제행 인덱스 저장

    // 각 행 위아래 행인덱스 저장
    vector<int> up, down;

    // 임시공간 포함한 위치 인덱스 초기화
    for (int i = 0; i < n + 2; i++) {
        up.push_back(i - 1);
        down.push_back(i + 1);
    }

    k++;  // 임시공간을 고려한 현재위치 넣기
    // 여기까지 초기화

    // 실제 cmd 명령어 처리 순회
    for (int i = 0; i < cmd.size(); i++) {
        // TO BE CONTINUED...
    }

    return answer;
}


int main()
{
    cout << "표 편집\n";

    // result = "OOOOXOOO"
    vector<string> cases1 = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z" };

    string result1 = solution(8, 2, cases1);

    cout << "result1 > " << result1 << endl;

    // result = "OOXOXOOO"
    vector<string> cases2 = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C" };

    string result2 = solution(8, 2, cases2);

    cout << "result2 > " << result2 << endl;

    return 0;
}
