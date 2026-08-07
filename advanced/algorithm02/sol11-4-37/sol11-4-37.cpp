// sol11-4-37.cpp : 너비우선탐색(BFS), 큐

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<int>> adjList;
vector<int> answer;

void bfs(int start) {
    unordered_set<int> visited;  // 방문여부.
    queue<int> qu;

    // 시작노드 방문
    qu.push(start);
    visited.insert(start);
    answer.push_back(start);

    while (!qu.empty()) { // 큐가 다 비면 탐색이 완료
        int node = qu.front();  // STL 스택,큐가 꺼낼값 확인, 꺼내는 동작 분리
        qu.pop();

        // 현재 노드의 인접노드 중 아직 방문하지 않는 노드 방문
        for (int neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                qu.push(neighbor);
                visited.insert(neighbor);
                answer.push_back(neighbor);
            }
        }
    }
}

vector<int> solution(vector<pair<int, int>> graph, int start) {

    adjList.clear();
    answer.clear();

    // 인접리스트 생성
    for (auto edge : graph) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
    }

    // 출력. 
    //for (auto it : adjList) {
    //    cout << it.first << " > ";

    //    for (auto st : it.second) {
    //        cout << st << ".";
    //    }
    //    cout << endl;
    //}

    // 너비우선탐색 함수 호출
    bfs(start);

    return answer;
}

int main() {
    cout << "BFS\n";

    cout << "테스트 케이스 1" << endl;
    vector<pair<int, int>> graph1 = { {1,2}, {1,3},{2,4},{2,5},{3,6},{3,7},{4,8},{5,8},{6,9},{7,9} };
    // result = {1,2,3,4,5,6,7,8,9}
    auto result1 = solution(graph1, 1);

    for (auto it : result1) {
        cout << it << ". ";
    }
    cout << endl;

    
    cout << "테스트 케이스 2" << endl;
    vector<pair<int, int>> graph2 = { {0,1}, {1,2},{2,3},{3,4},{4,5},{5,0} };
    // result = {1,2,3,4,5,0}
    auto result2 = solution(graph2, 1);

    for (auto it : result2) {
        cout << it << ". ";
    }
    cout << endl;

    // 451p 그림 예제
    cout << "테스트 케이스 3" << endl;
    vector<pair<int, int>> graph3 = { {1,4}, {1,5},{2,3},{5,1},{5,4},{4,2}, {4,3} };
    // result = {1, 4, 5, 2, 3}
    auto result3 = solution(graph3, 1);

    for (auto it : result3) {
        cout << it << ". ";
    }
    cout << endl;
    

    return 0;
}
