// sol11-4-39.cpp : 벨만-포드 알고리즘

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();  // 21억

vector<int> solution(int num_vertices, vector<tuple<int, int, int>> edges, int source) {
    vector<vector<pair<int, int>>> graph(num_vertices);

    // 간선 정보를 활용, 인접리스트 생성
    // 그래프 생성에서 가장 효율적인 방법
    for (auto& edge : edges) {
        int from, to, weight;
        tie(from, to, weight) = edge;
        graph[from].emplace_back(to, weight);
    }

    // distances 전부 INF로 설정, 시작노드만 0으로 초기화
    vector<int> distances(num_vertices, INF);
    distances[source] = 0;

    // 정점개수(num_vertices) -1 만큼 최소비용 갱신
    // graph에서 연결된 간선 개수만큼 반복
    for (int i = 0; i < num_vertices - 1; i++) {
        for (int u = 0; u < num_vertices; u++) {
            for (const auto [v, weight] : graph[u]) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;  // 최초에 전부 INF 라서 다 갱신
                }
            }
        }
    }

    // 음의 순환을 체크.
    for (int u = 0; u < num_vertices; u++) {
        for (const auto [v, weight] : graph[u]) {
            if (distances[u] + weight < distances[v]) { // 줄어드는 가중치가 있으며 음의 순환 존재!
                // 값 못구해!
                return vector<int>(1, -1);  // -1만 출력
            }
        }
    }

    return distances;
}

int main() {
    cout << "벨만-포드\n";

    cout << "테스트케이스 1" << endl;
    vector<tuple<int, int, int>> edges1 = { {0,1,4}, {0,2,3}, {0,4,-6}, {2,1,2}, {1,3,5}, {3,2,4},{3,0,7},{4,2,2} };
    auto result1 = solution(5, edges1, 0);
    // result1 = {0, 2, -4, 3, -6}
    for (auto it : result1) {
        cout << it << ". ";
    }
    cout << endl;

    cout << "테스트케이스 2" << endl;
    vector<tuple<int, int, int>> edges2 = { {0,1,5}, {0,2,-1}, {1,2,2}, {2,3,-2}, {3,0,2}, {3,1,6} };
    auto result2 = solution(4, edges2, 0);
    // result2 = {-1}
    for (auto it : result2) {
        cout << it << ". ";
    }
    cout << endl;

    return 0;
}
