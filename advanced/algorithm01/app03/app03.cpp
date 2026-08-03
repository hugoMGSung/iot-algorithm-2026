// app03.cpp : STL 컨테이너
// 벡터, 셋, 맵

#include <iostream>
// STL 라이브러리 헤더
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
    cout << "벡터 테스트" << endl;

    // 1차원 벡터 초기화
    vector<int> v1;    // 선언
    vector<int> v2 = { 1,2,3,4,5 };  // 선언 및 초기화
    vector<int> v3(4, 3); // 초기화, 크기 4로 모두 3일 채워라
    vector<int> v4(v3); // v3 복사 초기화 

    // 2차원 벡터
    vector<vector<int>> vv1;

    // 특정 크기로 초기화된 2차원 벡터
    int rows = 3; // 3행
    int cols = 4; // 4열

    vector<vector<int>> vv2(rows, vector<int>(cols));  // 3x4 2차원 벡터. 전부 0으로 초기화

    // 특정값으로 초기화 된 벡터
    int val = 9;
    vector<vector<int>> vv3(rows, vector<int>(cols, val));

    // 초기화 하면서 
    vector<vector<int>> vv4 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    // 1차원 벡터 출력
    for (int value : v2) {
        cout << value << ". ";
    }
    cout << endl;

    for (int value : v3) {
        cout << value << ". ";
    }
    cout << endl;

    // 2차원 벡터 출력
    for (const auto& row : vv4) {
        for (int value : row) {
            cout << value << ". ";
        }
        cout << endl;
    }
    cout << endl;

    // 벡터 원소 변경
    vector<int> vec = { 1,2,3,4,5 };

    vec[2] = 10;  // 인덱스2번 원소 변경   // 시간복잡도 : O(1)
    for (int value : vec) {
        cout << value << ". ";
    }
    cout << endl;

    // 벡터 원소 삽입/삭제  // 시간복잡도 : O(1)
    // 맨뒤 원소 삽입
    vec.push_back(6);  // 1, 2, 10, 4, 5, 6

    // 맨뒤 원소 삭제
    vec.pop_back();  // 1, 2, 10, 4, 5

    // 맨앞 원소 삽입
    vec.insert(vec.begin(), 0);   // 0, 1, 2, 10, 4, 5

    // 맨앞 원소 삭제
    vec.erase(vec.begin()); // 1, 2, 10, 4, 5




    // 셋
    cout << "셋 테스트" << endl;

    set<int> s1;
    set<int> s2 = { 3,1,3,2,5 };
    set<int> s3(s2);

    for (int value : s2) {
        cout << value << ". ";
    }
    cout << endl;

    // 한번에 여러 원소 찾기
    set<int> numbers = { 1, 2, 3, 4, 5, 6 };
    int targets[] = { 3, 7 };

    for (int target : targets) {
        // numbers에서 원소 탐색
        auto it = numbers.find(target);  // 시간복잡도 : O(logN)

        if (it != numbers.end()) {
            cout << "원소 " << target << "을 찾았습니다. 값 : " << *it << endl;
        }
        else {
            cout << "원소 " << target << "을 찾지 못했습니다." << endl;
        }
    }

    // 셋 원소 삽입, 삭제 // 시간복잡도 : O(logN)
    numbers.insert(8);
    numbers.erase(2);

    for (int number : numbers) {
        cout << number << ". ";  // 1, 3, 4, 5, 6, 8
    }
    cout << endl;

    // 특정원소 확인 후 삭제
    auto it = numbers.find(4);
    if (it != numbers.end()) {
        numbers.erase(*it);
    }

    // 삭제 후 출력
    for (int number : numbers) {
        cout << number << ". "; // 1, 3, 5, 6, 8
    }
    cout << endl;


    // 맵  삽입, 삭제, 검색 시간복잡도 : O(logN)
    cout << "맵 테스트" << endl;

    map<string, double> employeeSalaries;

    map<string, double> studentGrades = {
        {"John", 3.7},
        {"Emma", 3.9},
        {"Sophia", 4.0},
        {"Peter", 4.5}
    };  // 초기화

    for (auto it = studentGrades.begin(); it != studentGrades.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }  // Emma, John, Peter, Sophia

    // 특정키 접근
    // 배열처럼 [] 키로 검색, find() 로 검색
    map<string, int> studentScores;  // 선언 후 

    studentScores["Alice"] = 95;  // 데이터 삽입(할당) 키-값 쌍으로 추가
    studentScores["Bob"] = 88;
    studentScores["Charlie"] = 92;

    studentGrades["Marie"] = 3.8;  // Emma, John, Marie, Peter, Sophia

    // [] 연산자로 키를 사용, 값을 가져오기
    int score1 = studentScores["Alice"];
    cout << "Alice's Score : " << score1 << endl;

    int score2 = studentScores["Rabbit"];  // 없는 키로 가져오기
    cout << "Rabbit's Score : " << score2 << endl;   // 0. 가능한가? 실제 값이 0 이면??
    // ※ 위 처럼 하면 Rabbit 키를 자동 생성해서 0을 추가

    // find() 메서드로 검색을 할 것!
    auto result = studentScores.find("Charlie");
    if (result != studentScores.end()) {
        int score3 = result->second;
        cout << "Charlie's Score : " << score3 << endl;
    }

    // 새 키-값 쌍 삽입, 삭제
    studentScores.insert(make_pair("Kitty", 100));

    for (const auto& pair : studentScores) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 데이터 삭제
    studentGrades.erase("Peter");

    // 검색 후 삭제
    auto it2 = studentGrades.find("Sophia");
    if (it2 != studentGrades.end()) {
        studentGrades.erase(it2);
    }

    for (const auto& pair : studentGrades) {
        cout << pair.first << ": " << pair.second << endl;
    }  // Emma, John, Marie


    // 정렬되지 않은 셋, 맵
    // #include <unordered_set> <unordered_map>
    // unordered_map<string, int> testMap;

    return 0;
}