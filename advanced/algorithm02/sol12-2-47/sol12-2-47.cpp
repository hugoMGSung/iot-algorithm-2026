// sol12-2-47.cpp : 백트래킹

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> answer;
vector<int> selected_nums;
int target_num = 10;

// 유망함수 
void backtrack(int N, int sum, int start) {
    // sum이 target_num이면 조합을 결과에 추가
    if (sum == target_num) {
        answer.push_back(selected_nums);
        return;
    }

    for (int i = start; i <= N; i++) {
        // 합이 target_num보다 작으면 가능한 조합을 계속 확인
        if (sum + i <= target_num) {
            selected_nums.push_back(i);
            backtrack(N, sum + i, i + 1); 
            selected_nums.pop_back();
        }
    }
}

vector<vector<int>> solution(int N) {
    answer.clear();
    selected_nums.clear();

    backtrack(N, 0, 1);

    return answer;
}

int main() {
    cout << "백트래킹\n";

    cout << "테스트케이스 1" << endl;
    auto result1 = solution(5);

    for (auto it : result1) {
        for (auto st : it) {
            cout << st << ". ";
        }
        cout << endl;
    }

    cout << "테스트케이스 2" << endl;
    auto result2 = solution(2);

    for (auto it : result2) {
        for (auto st : it) {
            cout << st << ". ";
        }
        cout << endl;
    }

    cout << "테스트케이스 3" << endl;
    auto result3 = solution(7);

    for (auto it : result3) {
        for (auto st : it) {
            cout << st << ". ";
        }
        cout << endl;
    }
    
}
