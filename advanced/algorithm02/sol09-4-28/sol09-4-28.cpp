// sol09-4-28.cpp : 몸풀기 트리 순회

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 전위 순회
string preorder(vector<int> nodes, int idx) {
    if (idx < nodes.size()) {  // nodes가 크기 7인데 인덱스가 7보다 커질 수 없다
        string ret = to_string(nodes[idx]) + " ";
        ret += preorder(nodes, idx * 2 + 1);  // 인덱스가 0부터 시작
        ret += preorder(nodes, idx * 2 + 2);

        return ret;
    }
    else {
        return "";
    }
}

// 중위 순회
string inorder(vector<int> nodes, int idx) {
    if (idx < nodes.size()) {  // nodes가 크기 7인데 인덱스가 7보다 커질 수 없다
        string ret = inorder(nodes, idx * 2 + 1);  // 인덱스가 0부터 시작
        ret += to_string(nodes[idx]) + " ";
        ret += inorder(nodes, idx * 2 + 2);

        return ret;
    }
    else {
        return "";
    }
}

// 후위 순회
string postorder(vector<int> nodes, int idx) {
    if (idx < nodes.size()) {  // nodes가 크기 7인데 인덱스가 7보다 커질 수 없다
        string ret = postorder(nodes, idx * 2 + 1);  // 인덱스가 0부터 시작
        ret += postorder(nodes, idx * 2 + 2);
        ret += to_string(nodes[idx]) + " ";

        return ret;
    }
    else {
        return "";
    }
}



vector<string> solution(vector<int> nodes) {
    vector<string> answer;

    // 전위 순회 : 부모->왼->오른
    string pre_result = preorder(nodes, 0);
    // 중위 순회 : 왼->부모->오른
    string in_result = inorder(nodes, 0);
    // 후위 순회 : 왼->오른->부모
    string post_result = postorder(nodes, 0);

    answer.push_back(pre_result);
    answer.push_back(in_result);
    answer.push_back(post_result);

    return answer;
}

int main() {
    cout << "트리 순회\n";

    vector<int> nodes = { 1,2,3,4,5,6,7 };

    auto result = solution(nodes);

    for (auto it : result) {
        cout << it << ", ";
    }
    cout << endl;
}
