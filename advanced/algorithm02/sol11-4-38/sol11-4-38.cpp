// sol11-4-38.cpp : 다익스트라


#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();  // 21억
const int MAX_NODES = 10;  // 테스트케이스 갯수가 4개, 최소로 하고 나중에 숫자업
int graph[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];

vector<int> solution(int start, int numNodes, vector<tuple<int, int, int>> edges) {

    // 그래프 및 방문여부 초기화
    for (int i = 0; i < MAX_NODES; i++) {
        fill_n(graph[i], MAX_NODES, INF);   // 전부 무한대로 초기화
        visited[i] = false;
    }

    // 입력받은 간선 정보를 그래프로 표현
    for (const auto [from, to, weight] : edges) {
        graph[from][to] = weight;
    }

    // 시작 노드를 제외한 모든노드 최소비용을 INF 초기화
    vector<int> distances(numNodes, INF);
    distances[start] = 0; // 시작 노드

    for (int i = 0; i < numNodes - 1; i++) {
        int minDistance = INF;
        int closetNode = -1;

        // 최소거리 노드 찾기
        for (int j = 0; j < numNodes; j++) {
            // 방문하지 않은 노드이고, 거리값이 이전값보다 작으면
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                closetNode = j;
            }
        }

        visited[closetNode] = true;  // 찾은 노드 방문처리

        // 인접노드에 대한 거리 업데이트
        for (int j = 0; j < numNodes; j++) {
            int newDistance = distances[closetNode] + graph[closetNode][j];
            if (!visited[j] && graph[closetNode][j] != INF && newDistance < distances[j]) {
                distances[j] = newDistance;
            }
        }
    }

    return distances;
}


int main() {
    cout << "다익스트라 알고리즘\n";

    cout << "테스트 케이스1" << endl;
    vector<tuple<int, int, int>> edges1 = { {0,1,9}, {0,2,3}, {1,0,5}, {2,1,1} };
    auto result1 = solution(0, 3, edges1);

    for (auto it : result1) {
        cout << it << ". ";
    }
    cout << endl;

    
    cout << "테스트 케이스2" << endl;
    vector<tuple<int, int, int>> edges2 = { {0,1,1}, {1,2,5}, {2,3,1} };
    auto result2 = solution(0, 4, edges2);

    for (auto it : result2) {
        cout << it << ". ";
    }
    cout << endl;

    cout << "테스트 케이스3" << endl;
    vector<tuple<int, int, int>> edges3 = { {0,1,4}, {0,2,4}, {0,4,1}, {1,2,6}, {2,3,8}, {3,1,2},{3,0,5},{4,2,2} };
    auto result3 = solution(0, 5, edges3);
    // result3 = {0, 4, 3, 11, 1}

    for (auto it : result3) {
        cout << it << ". ";
    }
    cout << endl;

    cout << "테스트 케이스4" << endl; // 음의 순환
    // { {0,1,4}, {0,2,3}, {0,4,-6}, {2,1,2}, {1,3,5}, {3,2,4},{3,0,7},{4,2,2} };
    vector<tuple<int, int, int>> edges4 = { {0,1,5}, {0,2,-1}, {1,2,2}, {2,3,-2}, {3,0,2}, {3,1,6} };
    auto result4 = solution(0, 4, edges4);
    // result4 = {0, -2, -4, 3, -6}

    for (auto it : result4) {
        cout << it << ". ";
    }
    cout << endl;
}
