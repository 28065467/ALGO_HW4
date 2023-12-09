#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
struct Edge {
    int node1, node2;
    int weight;
    Edge(int n1, int n2, int w) {
        node1 = n1;
        node2 = n2;
        weight = w;
    }
    Edge() {
        node1 = 0;
        node2 = 0;
        weight = 0;
    }
    friend std::istream& operator>>(std::istream& input, Edge& e) {
        input >> e.node1 >> e.node2 >> e.weight;
        return input;
    }
};
bool cmp(Edge a, Edge b) {
    return a.weight < b.weight;
}
int main()
{
    int n, m, start, count = 0, total_weight = 0;
    cin >> n >> m;
    vector<vector<Edge>> edges(n + 1);
    for (int i = 0; i < m; i++) {
        Edge temp;
        cin >> temp.node1 >> temp.node2 >> temp.weight;
        Edge reverse_temp(temp.node2, temp.node1, temp.weight);
        edges[temp.node1].push_back(temp);
        edges[temp.node2].push_back(reverse_temp);
        sort(edges[temp.node1].begin(), edges[temp.node1].end(), cmp);
        sort(edges[temp.node2].begin(), edges[temp.node2].end(), cmp);
    }
    cin >> start;
    vector<int> ans(n + 1, 0);
    vector<int> selected_node;
    vector<bool> selected(n + 1, false);
    selected_node.push_back(start);
    selected[start] = true;
    while (count != n - 1) {
        int min = INT16_MAX, min_node, parent;
        for (int i = 0; i < selected_node.size(); i++) {
            vector<Edge> current_node_edges = edges[selected_node[i]];
            for (int j = 0; j < current_node_edges.size(); j++) {
                if (current_node_edges[j].weight < min) {
                    if (!selected[current_node_edges[j].node2]) {
                        parent = selected_node[i];
                        min = current_node_edges[j].weight;
                        min_node = current_node_edges[j].node2;
                    }
                }
            }
        }
        total_weight += min;
        selected_node.push_back(min_node);
        selected[min_node] = true;
        ans[min_node] = parent;
        count++;
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << endl << total_weight << endl;
}