// app02.cpp : STL 컨테이너 타입 활용
// Call by Value/Reference
// 반복자

#include <iostream>
// 2. 필요 프리프로세서 추가
#include <vector>
#include <map>
#include <set>
#include <string>
// 4. find 함수의 헤더
#include <algorithm>

using namespace std;

void modifyByValue(int value) {
    value = 10;   
    cout << "2. 주소 : " << &value << endl;  // 0000004B76B7F7F0
    cout << "2. 값   : " << value << endl;  // 10

    // 함수가 종료되면 value는 메모리에서 사라짐!
}

void modifyByReference(int& value) {
    value = 15;
    cout << "4. 주소 : " << &value << endl;  // 0000004B76B7F814
    cout << "4. 값   : " << value << endl;  // 15
}

int main()
{
    // 1. 상수 레퍼런스
    // `Call by Value` vs `Call by reference`
    // 컨테이너 객체, 구조체를 Call by Value로 넘기면 성능에 지대한 영향
    int value = 5;
    cout << "1. 주소 : " << &value << endl;  // 0000004B76B7F814
    cout << "1. 값   : " << value << endl;  // 5

    modifyByValue(value);  // 함수 호출
    cout << "3. 주소 : " << &value << endl;  // 0000004B76B7F814
    cout << "3. 값   : " << value << endl;  // 5

    modifyByReference(value);  // 
    cout << "5. 주소 : " << &value << endl;  // 0000004B76B7F814
    cout << "5. 값   : " << value << endl;  // 15

    // 2. auto문  -> javascript, C#의 var 와 동일
    auto num = 42;   // int로 추론
    cout << num << endl;

    auto pi = 3.141592;  // double로 추론
    cout << pi << endl;

    auto greeting = string("Hello, C++!");  // string으로 추론
    cout << greeting << endl;

    // 3. 범위기반 반복문 foreach, for in
    // 컨테이너 등에서 모든 원소를 반복적 순회

    // vector : 1차원 배열
    cout << "벡터 " << endl;
    vector<int> vec = { 1,2,3,4,5 };
    for (const auto& num : vec) {  // for (int num : vec) {
        cout << num << ". ";
    }
    cout << endl;

    // map : Dictionary
    cout << "맵 " << endl;
    map<string, int> fruitMap = { {"apple", 1}, {"banana", 2}, {"mango", 3}, {"cherry", 4} };
    for (const auto& pair : fruitMap) { // for (auto pair : fruitMap) {
        cout << pair.first << " => " << pair.second << ". ";
    }
    cout << endl;

    // set : 집합
    cout << "집합 " << endl;
    set<string> fruitSet = { "apple", "banana", "mango", "cherry", "banana" };
    for (const auto& fruit : fruitSet) {  // for (string fruit : fruitSet) {
        cout << fruit << ". ";
    }
    cout << endl;

    // 4. 반복자 - vector, map, set 등 컨테이너를 종류와 관계없이 원소 순회 접근가능하도록 처리
    cout << "반복자 " << endl;
    vector<int> vec2 = { 10,20,30,40,50,60,70,80,90,100 };

    // 반복자 순회
    for (auto it = vec2.begin(); it != vec2.end(); ++it) {
        cout << *it << ". ";
    }
    cout << endl;

    // 탐색
    auto result = find(vec2.begin(), vec2.end(), 40);
    if (result != vec2.end()) {
        cout << "Found : " << *result << endl; // Found : 40
    } 
    else {
        cout << "Not found." << endl;
    }

    // 역방향 반복자
    for (auto it = vec2.rbegin(); it != vec2.rend(); ++it) {
        cout << *it << ". ";
    }
    cout << endl;
    
    // fruitMap 순회
    for (auto it = fruitMap.begin(); it != fruitMap.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // 원소 탐색
    auto result2 = fruitMap.find("mango");
    if (result2 != fruitMap.end()) {
        cout << "Found : " << result2->first << "=> " << result2->second << endl;
    }
    else {
        cout << "Not found." << endl;
    }

    return 0;
}
