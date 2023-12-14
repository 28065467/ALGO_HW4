#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<float>> dist(n + 1, vector<float>(n + 1, INT16_MAX));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int start, end;
        float weight;
        cin >> start >> end >> weight;
        dist[start][end] = weight;
    }

    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INT16_MAX && dist[k][j] != INT16_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Output the shortest distances
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INT16_MAX) {
                cout << "N" << ((j == n) ? "" : " ");
            } else {
                cout << dist[i][j] << ((j == n) ? "" : " ");
            }
        }
        cout << endl;
    }

    return 0;
}
