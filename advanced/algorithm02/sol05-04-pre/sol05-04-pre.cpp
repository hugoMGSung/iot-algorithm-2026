// sol05-04-pre.cpp : 요일 패턴 테스트
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    cout << "요일 테스트\n";

    vector<string> days = { "월", "화", "수", "목", "금", "토", "일" };

	for (int i = 0; i <= 30; i++)
	{
		cout << days[i % days.size()] << ", ";
	}
	cout << endl;
}

