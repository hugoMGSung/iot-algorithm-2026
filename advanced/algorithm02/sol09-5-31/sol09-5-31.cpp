// sol09-5-31.cpp : 다단계 칫솔 판매

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    unordered_map<string, string> parent;

    // parent는 판매원 - 판매원 추천인 쌍으로 생성
    for (int i = 0; i < enroll.size(); i++) {
        parent[enroll[i]] = referral[i];  // { john : -, mary : -, edward : mary }
    }

    // parent 생성 결과 확인 - 주석처리
    for (auto it : parent) {
        cout << it.first << " : " << it.second << endl;
    }

    // 판매금액, 분배금 담을 맵 생성
    unordered_map<string, int> total;
    // 판매원 - 판매원 수익 구성, 최초에는 0으로 초기화
    for (const auto& name : enroll) {
        total[name] = 0;
    }

    //// total 결과 확인 - 주석처리
    //for (auto it : total) {
    //    cout << it.first << " : " << it.second << endl;
    //}

    // seller 판매자 길이만큼 반복하면서
    // 매핑되는 amount 갯수로 판매금액 total에 할당
    // O(N)
    for (int i = 0; i < seller.size(); i++) {
        int money = amount[i] * 100; // 현재 판매금 계산
        string cur_seller_name = seller[i]; // 현재 판매자 이름

        // 금액이 0보다 크고, curr_seller_name이 "-" 아닐때까지 계속 반복
        // O(M) or O(logM) 예상
        while (money > 0 && cur_seller_name != "-") {
            int dist_money = money / 10;  // 추천인에게 분배할 10% 금액 구하기
            total[cur_seller_name] += money - dist_money;

            // 현재 이름의 추천인이 있으면 현재이름을 추천인으로 변경, 아니면 종료
            if (parent.find(cur_seller_name) != parent.end()) {
                cur_seller_name = parent[cur_seller_name];
            }
            else {
                break;
            }

            // 현재 판매원이 추천인으로 변경. 수익금 업데이트 필요
            money = dist_money;
        }
    }

    // total 결과 확인 - 주석처리
    for (auto it : total) {
        cout << it.first << " : " << it.second << endl;
    }

    // total에 들어있는 수익금을 answer에 옮김
    vector<int> answer;
    answer.reserve(total.size());  // 크기만 예약

    // 금액만 enroll의 순서대로 담는 벡터 생성
    for (const auto& name : enroll) {
        answer.push_back(total[name]);
    }

    return answer;
}

int main() {
    cout << "다단계 칫솔 판매\n";

    cout << "테스트케이스 1" << endl;
    vector<string> enroll1 = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
    vector<string> referral1 = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller1 = { "young", "john", "tod", "emily", "mary" };
    vector<int> amount1 = { 12, 4, 2, 5, 10 };
    // result1 = {360, 958, 108, 0, 450, 18, 180, 1080}

    auto result1 = solution(enroll1, referral1, seller1, amount1);
    for (auto it : result1) {
        cout << it << ". ";
    }
    cout << endl;

    cout << "테스트케이스 2" << endl;
    vector<string> enroll2 = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
    vector<string> referral2 = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller2 = { "sam", "emily", "jaimie", "edward" };
    vector<int> amount2 = { 2, 3, 5, 4 };
    // result2 = {0, 110, 378, 180, 270, 450, 0, 0}

    auto result2 = solution(enroll2, referral2, seller2, amount2);
    for (auto it : result2) {
        cout << it << ". ";
    }
    cout << endl;

    return 0;
}
