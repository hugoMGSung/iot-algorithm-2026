// app04.cpp : STL 제공 알고리즘
//

#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

// 비교함수
bool compare(const Point& a, const Point& b) {
    if (a.x == b.x) {
        return a.y < b.y;   // x가 같으면 y가 작은 순서대로 정렬
    }
    return a.x < b.x;     // x가 작은 순서대로 정렬
}

int main()
{
    cout << "STL 제공 알고리즘" << endl;

    // count()    O(N)
    cout << "count()" << endl;

    vector<int> vec = { 1,4,3,4,5,4,5 };

    // 5가 몇번 나타나는지 카운팅
    int ret = count(vec.begin(), vec.end(), 5);
    cout << "5 갯수 : " << ret << endl;

    // sort()   O(NlogN)
    cout << "sort()" << endl;

    vector<int> vec_origin = { 4, 6, 9, 2, 7, 5, 2, 3, 1, 0 };

    for (auto it = vec_origin.begin(); it != vec_origin.end(); ++it) {
        cout << *it << ". ";
    }
    cout << endl;

    sort(vec_origin.begin(), vec_origin.end()); // 오름차순 정렬

    for (auto it = vec_origin.begin(); it != vec_origin.end(); ++it) {
        cout << *it << ". ";
    }
    cout << endl;

    sort(vec_origin.rbegin(), vec_origin.rend()); // 내림차순 정렬

    for (auto it = vec_origin.begin(); it != vec_origin.end(); ++it) {
        cout << *it << ". ";
    }
    cout << endl;

    // sort() 중 세번째 매개변수 사용하는 방법
    vector<Point> points = { {3, 4}, {1, 2}, {3, 1}, {2, 5}, {1, 1} };

    for (const Point& p : points) {
        cout << "{" << p.x << ", " << p.y << "} ";
    }
    cout << endl;

    // points 벡터를 사용자 정의 기준으로 정렬
    sort(points.begin(), points.end(), compare);

    for (const Point& p : points) {
        cout << "{" << p.x << ", " << p.y << "} ";
    }
    cout << endl;


    // 순열 next_permutation()  O(N*N!)
    cout << "next_permutation()" << endl;

    vector<int> vec4 = { 1,2,3 }; // 정렬이 완료된 후 순열 생성

    // 가능한 모든 순열 출력
    do {
        for (int i : vec4) {
            cout << i << ". ";
        }
        cout << endl;
    } while (next_permutation(vec4.begin(), vec4.end()));

    // unique() - 중복제거 O(N)
    cout << "unique()" << endl;

    vector<int> vec5 = { 1,2,2,3,3,3,4,4,5,5,5,6,6, };

    auto newEnd = unique(vec5.begin(), vec5.end());

    // 중복되지 않는 요소만 출력
    for (auto it = vec5.begin(); it != newEnd; it++) {
        cout << *it << ". ";
    }
    cout << endl;

    // binary_search()  O(logN)
    cout << "binary_search()" << endl;

    vector<int> vec6 = { 1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15 };

    cout << binary_search(vec6.begin(), vec6.end(), 3) << endl;  // 1
    cout << binary_search(vec6.begin(), vec6.end(), 17) << endl;  // 0

    // max_element(), min_element()  O(N)
    cout << "max(min)_element()" << endl;

    vector<int> vec7 = { 1,3,5,7,2,4,6, 8 };

    auto maxIt = max_element(vec7.begin(), vec7.end());
    auto minIt = min_element(vec7.begin(), vec7.end());

    cout << *maxIt << endl;  // 8
    cout << *minIt << endl;  // 1

    return 0;
}