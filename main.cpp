#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

void dijkstra(int source, const vector<vector<Edge>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<Edge>> graph(n);

    cout << "Enter the edges in the format: from to weight" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // if the graph is undirected
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    vector<int> dist;
    dijkstra(source, graph, dist);

    cout << "Shortest distances from vertex " << source << " to all other vertices:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "To vertex " << i << ": " << dist[i] << endl;
    }

    return 0;
}
