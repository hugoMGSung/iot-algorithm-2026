// sol08-5-27.cpp : 메뉴 리뉴얼

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> combi;  // 주문 조합 변수

// src 문자열로 만들 수 있는 depth 길이만큼의 문자열 경우의 수
void combination1(string src, string dst, int depth) {
    if (dst.size() == depth)
        cout << dst << endl;
    else {
        for (int i = 0; i < src.size(); i++) {
            combination1(src.substr(i + 1), dst + src[i], depth); // 재귀호출
        }
    }
}

// 실제 주문 조합을 구하는 함수
void combination(string src, string dst, int depth) {
    if (dst.size() == depth) combi[dst]++;  // 맵에 추가
    else {
        for (int i = 0; i < src.size(); i++) {
            combination(src.substr(i + 1), dst + src[i], depth); // 재귀호출
        }
    }
}


vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    // 주문을 알파벳순 정렬
    for (string& order : orders) {
        sort(order.begin(), order.end());
    }

    // 정렬 확인
    //for (auto it : orders) {
    //    cout << it << ". ";
    //}
    //cout << endl;

    for (int len : course) {  // 
        for (string order : orders) {
            // course 길이별 조합 생성
            combination(order, "", len); // O(N^2 * 2^M)
        }

        // 각 길이별로 구해진 조합 빈도수 순회하면서 maxOrder를 저장
        int maxOrder = 0;
        for (auto it : combi) {
            maxOrder = max(maxOrder, it.second); // O(N^2)
        }

        // 주문회수가 2회 이상, 가장 많이 주문된 구성을 answer에 추가
        for (auto it : combi) {
            if (maxOrder >= 2 && it.second == maxOrder) {
                answer.push_back(it.first);
            }
        }

        combi.clear();
    }

    // 주문 구성을 오름차순으로 정렬
    sort(answer.begin(), answer.end());
    return answer;
}

int main()
{
    cout << "메뉴 리뉴얼\n";

    cout << "조합 테스트" << endl;
    combination1("ABC", "", 2);

    cout << "1번 케이스" << endl;
    vector<string> order1 = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    vector<int> course1 = { 2,3,4 };
    // result = {"AC", "ACDE", "BCFG", "CDE"}
    vector<string> result1 = solution(order1, course1);

    for (auto item : result1) {
        cout << item << ". ";
    }
    cout << endl;

    cout << "2번 케이스" << endl;
    vector<string> order2 = { "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" };
    vector<int> course2 = { 2,3,5 };
    // result = {"ACD", "AD", "ADE", "CD", "XYZ"}
    vector<string> result2 = solution(order2, course2);

    for (auto item : result2) {
        cout << item << ". ";
    }
    cout << endl;

    cout << "3번 케이스" << endl;
    vector<string> order3 = { "XYZ", "XWY", "WXA" };
    vector<int> course3 = { 2,3,4 };
    // result = {"WX", "XY"}
    vector<string> result3 = solution(order3, course3);

    for (auto item : result3) {
        cout << item << ". ";
    }
    cout << endl;

    return 0;
}
