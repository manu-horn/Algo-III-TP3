#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
int casos, n, m, k, s, t;
const int  INF = 1e18;
vector<vector<pair<int,int>>> adj;
vector<vector<pair<int,int>>> adj_inv;
vector<tuple<int,int,int>> candidatas;

vector<int> dijkstra(int x, vector<vector<pair<int,int>>>& adj){
    vector<int> distance(n+1);
    priority_queue<pair<int,int>> q;
    vector<int> processed(n+1, false);

    for (int i = 1; i <= n; i++) distance[i] = INF;
    distance[x] = 0; q.push({0,x});
    while (!q.empty()) {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (distance[a]+w < distance[b]) {
                distance[b] = distance[a]+w;
                q.push({-distance[b],b});
            }
        }
    }
    return distance;
}

int main() {

    cin >> casos;

    for (int i = 0; i < casos; i++) {
        cin >> n >> m >> k >> s >> t;
        adj.clear();
        adj.resize(n + 1);
        adj_inv.clear();
        adj_inv.resize(n + 1);
        for (int j = 0; j < m; j++) {
            int d, c, l;
            cin >> d >> c >> l;
            adj[d].push_back({c, l});
            adj_inv[c].push_back({d, l});
        }
        candidatas.clear();
        for (int j = 0; j < k; j++) {
            int u, v, q;
            cin >> u >> v >> q;
            candidatas.push_back({u, v, q});
        }

    vector<int> distS = dijkstra(s, adj);
    vector<int> distT = dijkstra(t, adj_inv);
    int actual = distS[t];

    for(int i=0;i<k;i++){
        actual = min(actual, distS[get<0>(candidatas[i])] + get<2>(candidatas[i]) + distT[get<1>(candidatas[i])]);
        actual = min(actual, distS[get<1>(candidatas[i])] + get<2>(candidatas[i]) + distT[get<0>(candidatas[i])]);
    }
    cout << actual << endl;
    }
    return 0;
}

