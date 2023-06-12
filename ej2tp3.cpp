#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int INF = 1e18;
vector<vector<int>> adj;
vector<vector<int>> capacity;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(adj.size());
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0){
            break;
        }
        int s = 0;  // Fuente
        int t = n + 1;  // Sumidero
        adj.clear();
        adj.resize(n + 2);
        capacity.clear();
        capacity.resize(n+2, vector<int>(n+2));
        for (int i = 1; i <= n; i++) {
            int creencia;
            cin >> creencia;
            if (creencia) {
                adj[s].push_back(i);
                capacity[s][i]=1;
            } else {
                adj[i].push_back(t);
                capacity[i][t]=1;
            }
        }

        for (int i = 0; i < m; i++) {
            int j, v;
            cin >> j >> v;
            adj[v].push_back(j);
            adj[j].push_back(v);
            capacity[v][j] = 1;
            capacity[j][v] = 1;
        }

        int result = maxflow(s, t);
        cout << result << endl;
    }
    return 0;
}