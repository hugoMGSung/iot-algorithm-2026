// sol08-5-20.cpp : 완주하지 못한 선수

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {   
    map<string, int> ph;  // 참여자 해시테이블

    // 참가자를 전부 해시테이블에 추가
    for (int i = 0; i < participant.size(); i++) {
        ph[participant[i]] += 1;
    }

    // 참가자 정보 해시테이블에서 완주한 선수 제외
    for (int i = 0; i < completion.size(); i++) {
        ph[completion[i]] -= 1;

        // 해시테이블에서 키(이름) 값이 0인 데이터는 삭제
        if (ph[completion[i]] == 0)
            ph.erase(ph.find(completion[i]));
    }

    // 마지막 남은 한 선수 이름 반환
    return ph.begin()->first;
}

int main() {
    cout << "완주하지 못한 선수\n";

    vector<string> participant1 = { "leo", "kiki", "eden" };
    vector<string> completion1 = { "eden", "kiki" };

    auto result = solution(participant1, completion1);
    cout << result << endl;

    vector<string> participant2 = { "marina", "josipa", "nikola", "vinko", "filipa" };
    vector<string> completion2 = { "josipa", "filipa", "marina", "nikola" };

    result = solution(participant2, completion2);
    cout << result << endl;

    vector<string> participant3 = { "mislav", "stanko", "mislav", "ana" };
    vector<string> completion3 = { "stanko", "ana", "mislav" };

    result = solution(participant3, completion3);
    cout << result << endl;
}
