// sol11-4-36.cpp : 깊이우선탐색(DFS) - 스택 또는 재귀호출

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, vector<char>> adjList;
vector<char> answer;
unordered_set<char> visited;

void dfs(char node) {
    // 현재 방문한 노드를 방문목록과 경로에 추가
    visited.insert(node);
    answer.push_back(node);

    // 현재 노드와 인접한 노드 중, 방문하지 않은 노드에 깊이 우선탐색 진행
    for (char neighbor : adjList[node]) {
        if (visited.find(neighbor) == visited.end()) { // 방문한 노드가 없음
            dfs(neighbor);  // 재귀호출
        }
    }
}

vector<char> solution(vector<pair<char, char>> graph, char start) {

    adjList.clear();
    answer.clear();
    visited.clear(); // 테스트케이스 여러개 풀면 전역변수 초기화 필요
    
    // 인접리스트 생성
    for (auto& edge : graph) {
        char u = edge.first;
        char v = edge.second;

        adjList[u].push_back(v);
    }

    // 시작노드부터 DFS 시작
    dfs(start);

    return answer;
}

int main() {
    cout << "DFS\n";

    cout << "테스트 케이스1 " << endl;
    vector<pair<char, char>> graph1 = { {'A', 'B'}, {'B', 'C'}, {'C','D'}, {'D', 'E'} };
    char start1 = 'A';

    auto result1 = solution(graph1, start1);

    for (auto it : result1) {
        cout << it << ". " ;
    }
    cout << endl;

    cout << "테스트 케이스2 " << endl;
    vector<pair<char, char>> graph2 = { {'A', 'B'}, {'A', 'C'}, {'B','D'}, {'B', 'E'}, {'C', 'F' },{'E', 'F'} };
    char start2 = 'A';

    auto result2 = solution(graph2, start2);

    for (auto it : result2) {
        cout << it << ". ";
    }
    cout << endl;

    return 0;
}
