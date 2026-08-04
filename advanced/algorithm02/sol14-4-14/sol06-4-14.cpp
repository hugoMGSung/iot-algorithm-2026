// sol06-4-14.cpp : 표 편집
//

#include <iostream>
#include <vector>
#include <stack>
#include <string>   // 문자열 함수 

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
        // 삭제 명령어면
        if (cmd[i][0] == 'C') {  // 삭제 명령처리
            deleted.push(k);  // 삭제된 인덱스 스택에 추가
            down[up[k]] = down[k];
            up[down[k]] = up[k];

            // 벡터 크기를 벗어났으면, 아래쪽으로 범위를 벗어났다면
            if (down[k] == n + 1)
                k = up[k];
            else
                k = down[k];
        }
        else if (cmd[i][0] == 'Z') {  // 복구 명령처리
            int r = deleted.top(); // 스택 맨 위에있는 인덱스 가져옴
            down[up[r]] = r;
            up[down[r]] = r;
            
            deleted.pop();
        }
        else {  // D, U 시작하는 명령처리
            int sz = stoi(cmd[i].substr(2));     // "D 2", "U 3", "D 4", "D 300000"

            if (cmd[i][0] == 'U') { // U -> 위로 이동
                for (int j = 0; j < sz; j++) {
                    k = up[k];
                }
            }
            else if (cmd[i][0] == 'D') { // D -> 아래로 이동
                for (int j = 0; j < sz; j++) {
                    k = down[k];  // k가 2일때 가상환경때문 1추가, 2만큼 반복하면 k = 5
                }
            }
        }
    }

    // 삭제된 행의 위치에 'X' 표시, 그 외는 'O' 표시하는 문자열
    answer.append(n, 'O');
    while (!deleted.empty()) {
        // delted.top() 들어있는 값은 가상공간을 늘려서 인덱스가 증가된 상태기 때문에
        // -1을 해야 실제 인덱스로 바뀜
        answer[deleted.top() - 1] = 'X';  // OOOOOOOO -> OOOOXOOO

        deleted.pop(); // 사용한 인덱스는 지움
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
