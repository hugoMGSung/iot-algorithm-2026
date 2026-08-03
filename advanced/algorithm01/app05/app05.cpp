// app05.cpp : 함수
//

#include <iostream>

using namespace std;

// 더하기 함수
int add(int param1, int param2) {
    return param1 + param2;
}

int main()
{
    cout << "함수!\n";

    int a = 5;
    int b = 10;

    cout << add(a, b) << endl;
}
