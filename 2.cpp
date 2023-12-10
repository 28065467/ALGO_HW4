#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
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
bool cmp(Edge a, Edge b) {
    return a.weight < b.weight;
}
int main()
{
    int n, m, start;
    cin >> n >> m;
    vector<vector<Edge>> edges(n + 1);
    for (int i = 0; i < m; i++) {
        Edge temp;
        cin >> temp.start >> temp.end >> temp.weight;
        edges[temp.start].push_back(temp);
        sort(edges[temp.start].begin(), edges[temp.start].end(), cmp);
    }
    vector<int> ans_weight(n + 1, INT16_MAX);
    vector<int> ans_parent(n + 1);
    vector<int> Selected_Node;
    vector<bool> Selected(n + 1,false);
    cin >> start;
    ans_weight[start] = 0;
    ans_parent[start] = 0;
    Selected_Node.push_back(start);
    Selected[start] = true;
    int count = 0;
    while (count != n - 1)
    {
        for (int i = 1; i <= n; i++) { // Choose the destination
            if (i == start)
                continue;
            for (int j = 0; j < Selected_Node.size(); j++) {
                vector<Edge> Current_Node_Edge = edges[Selected_Node[j]];
                for (int k = 0; k < Current_Node_Edge.size(); k++) {
                    if (Current_Node_Edge[k].end == i) {
                        if (ans_weight[Current_Node_Edge[k].start] + Current_Node_Edge[k].weight < ans_weight[Current_Node_Edge[k].end]) {
                            ans_weight[Current_Node_Edge[k].end] = ans_weight[Current_Node_Edge[k].start] + Current_Node_Edge[k].weight;
                            ans_parent[Current_Node_Edge[k].end] = Current_Node_Edge[k].start;
                        }
                    }
                }
            }
        }
        int current_min = INT16_MAX, min_index;
        for (int i = 1; i <= n; i++) {
            if (ans_weight[i] < current_min && !Selected[i]) {
                current_min = ans_weight[i];
                min_index = i;
            }
        }
        Selected[min_index] = true;
        Selected_Node.push_back(min_index);
        count++;
    }
    for (int i = 1; i <= n; i++)
        cout << ans_weight[i] << " ";
    cout << endl;
    for (int i = 1; i <= n; i++)
        cout << ans_parent[i] << " ";
}