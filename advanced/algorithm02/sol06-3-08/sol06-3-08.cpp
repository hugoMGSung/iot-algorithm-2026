// sol06-3-08.cpp : 괄호 짝 맞추기 == 올바른 괄호
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool solution(string s) {   // "()()(("
    bool answer = true;
    stack<char> stack;

    for (char c : s) {
        //cout << c << ",";
        if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            if (stack.empty()) {
                answer = false;
                return answer;
            }
            else {
                stack.pop();  // 스택에 있늘 걸 빼면됨
            }
        }
    }
    answer = stack.empty(); // 다 끝난후 스택이 비어있으면 true 
    //cout << endl;
    return answer;
}

int main() {
    cout << "TEST CASE 1" << endl;
    string cases1 = "()()";
    cout << solution(cases1) << endl;

    cout << "TEST CASE 2" << endl;
    string cases2 = "(())()";
    cout << solution(cases2) << endl;

    cout << "TEST CASE 3" << endl;
    string cases3 = ")()(";
    cout << solution(cases3) << endl;

    cout << "TEST CASE 4" << endl;
    string cases4 = "(()(";
    cout << solution(cases4) << endl;

    cout << "TEST CASE 5" << endl;
    string cases5 = "((())()";
    cout << solution(cases5) << endl;
}