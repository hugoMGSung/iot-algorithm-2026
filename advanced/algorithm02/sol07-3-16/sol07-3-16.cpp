// sol07-3-16.cpp : 카드 뭉치

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
	queue<string> c1, c2, g;

	// 모든 벡터자료형으로 큐로 변경
	for (const string& s : cards1) c1.push(s);
	for (const string& s : cards2) c2.push(s);
	for (const string& s : goal) g.push(s);

	// goal이 다 빌때까지
	while (!g.empty()) {
		if (!c1.empty() && c1.front() == g.front()) {  // cards1 맨 앞데이터와 goal 맨 앞데이터가 일치하면
			c1.pop();
			g.pop();
		}
		else if (!c2.empty() && c2.front() == g.front()) {  // cards2 맨 앞데이터와 goal 맨 앞데이터가 일치하면
			c2.pop();
			g.pop();
		}
		else { // 일치하는 카드가 cards1, card2번에 모두 없으면 끝
			break;
		}
	}

	string answer = g.empty() ? "Yes" : "No";

	return answer;
}

int main() {   
	cout << "카드뭉치\n";

	vector<string> cards1_1 = { "i", "drink", "water" };
	vector<string> cards1_2 = { "want", "to" };
	vector<string> goal1 = { "i", "want", "to", "drink", "water" };

	auto result = solution(cards1_1, cards1_2, goal1);
	cout << result << endl;

	vector<string> cards2_1 = { "i", "water", "drink" };
	vector<string> cards2_2 = { "want", "to" };
	vector<string> goal2 = { "i", "want", "to", "drink", "water" };

	result = solution(cards2_1, cards2_2, goal2);
	cout << result << endl;	
}
