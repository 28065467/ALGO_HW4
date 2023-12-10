#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // Add this header for INT_MAX
using namespace std;

struct Edge {
    int start, end;
    int weight;
    Edge(int n1, int n2, int w) {
        start = n1;
        end = n2;
        weight = w;
    }
    Edge() {
        start = 0;
        end = 0;
        weight = 0;
    }
    friend std::istream& operator>>(std::istream& input, Edge& e) {
        input >> e.start >> e.end >> e.weight;
        return input;
    }
};

int main() {
    int n, m, start;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i];
    }

    cin >> start;

    vector<int> ans_weight(n + 1, INT_MAX);
    vector<int> ans_parent(n + 1, 0);

    ans_weight[start] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (const Edge& e : edges) {
            if (ans_weight[e.start] != INT_MAX && ans_weight[e.start] + e.weight < ans_weight[e.end]) {
                ans_weight[e.end] = ans_weight[e.start] + e.weight;
                ans_parent[e.end] = e.start;
            }
        }
    }

    // Check for negative cycles
    for (const Edge& e : edges) {
        if (ans_weight[e.start] != INT_MAX && ans_weight[e.start] + e.weight < ans_weight[e.end]) {
            cout << "There is a negative weight cycle in the graph" << endl;
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans_weight[i] << " ";
    }
    cout << endl;

    for (int i = 1; i <= n; i++) {
        cout << ans_parent[i] << " ";
    }

    return 0;
}
