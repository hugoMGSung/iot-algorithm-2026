#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge
{
    int from;
    int to;
    int cost;
};

struct BellmanFordResult
{
    vector<int> distance;
    vector<int> previous;
    bool hasNegativeCycle;
};

BellmanFordResult solution(
    int nodeCount,
    const vector<Edge>& edges,
    int start)
{
    const int INF = numeric_limits<int>::max();

    vector<int> distance(nodeCount, INF);
    vector<int> previous(nodeCount, -1);

    distance[start] = 0;

    // 정점 개수 - 1번 반복
    for (int i = 0; i < nodeCount - 1; i++)
    {
        bool updated = false;

        for (const Edge& edge : edges)
        {
            // 출발 정점에 도달할 수 없는 경우
            if (distance[edge.from] == INF)
                continue;

            int newDistance =
                distance[edge.from] + edge.cost;

            if (newDistance < distance[edge.to])
            {
                distance[edge.to] = newDistance;
                previous[edge.to] = edge.from;
                updated = true;
            }
        }

        // 더 이상 갱신되지 않으면 조기 종료
        if (!updated)
            break;
    }

    // 음수 사이클 검사
    bool hasNegativeCycle = false;

    for (const Edge& edge : edges)
    {
        if (distance[edge.from] == INF)
            continue;

        if (distance[edge.from] + edge.cost
            < distance[edge.to])
        {
            hasNegativeCycle = true;
            break;
        }
    }

    return {
        distance,
        previous,
        hasNegativeCycle
    };
}

vector<int> makePath(
    int destination,
    const vector<int>& previous)
{
    vector<int> path;

    for (int current = destination;
        current != -1;
        current = previous[current])
    {
        path.push_back(current);
    }

    reverse(path.begin(), path.end());

    return path;
}

int main()
{
    // A=0, B=1, C=2, D=3, E=4
    const int NODE_COUNT = 5;

    vector<char> nodeNames = {
        'A', 'B', 'C', 'D', 'E'
    };

    vector<Edge> edges = {
        {0, 1,  4},   // A -> B
        {0, 2,  3},   // A -> C
        {0, 4, -6},   // A -> E
        {1, 3,  5},   // B -> D
        {2, 1,  2},   // C -> B
        {3, 0,  7},   // D -> A
        {3, 2,  4},   // D -> C
        {4, 2,  2}    // E -> C
    };

    int start = 0;  // 출발 정점 A

    BellmanFordResult result =
        solution(NODE_COUNT, edges, start);

    if (result.hasNegativeCycle)
    {
        cout << "음수 사이클이 존재합니다.\n";
        return 0;
    }

    cout << "출발 정점: "
        << nodeNames[start] << "\n\n";

    cout << "노드\t최소 비용\t직전 정점\n";

    for (int i = 0; i < NODE_COUNT; i++)
    {
        cout << nodeNames[i] << "\t"
            << result.distance[i] << "\t\t";

        if (result.previous[i] == -1)
            cout << "-";
        else
            cout << nodeNames[result.previous[i]];

        cout << '\n';
    }

    cout << "\n최단 경로\n";

    for (int i = 0; i < NODE_COUNT; i++)
    {
        vector<int> path =
            makePath(i, result.previous);

        cout << nodeNames[start]
            << " -> "
            << nodeNames[i]
            << " : ";

        for (int j = 0;
            j < static_cast<int>(path.size());
            j++)
        {
            cout << nodeNames[path[j]];

            if (j < path.size() - 1)
                cout << " -> ";
        }

        cout << " (비용: "
            << result.distance[i]
            << ")\n";
    }

    return 0;
}