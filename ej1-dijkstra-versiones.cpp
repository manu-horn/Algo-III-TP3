#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <set>

using namespace std;
int casos, n, m, k, s, t;
const int  INF = 999999;
vector<vector<pair<int,int>>> adj;
vector<vector<pair<int,int>>> adj_inv;
vector<tuple<int,int,int>> candidatas;

/*
vector<int> dijkstra(int x, vector<vector<pair<int,int>>>& adj){ // priority queue (ralos)
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
*/

/*
vector<int> dijkstra(int s, vector<vector<pair<int,int>>> adj) { //set: red-black tree (ralos)
    int n = adj.size();
    vector<int> d(n+1, INF);
    vector<int> p(n+1, -1);

    d[s] = 0;
    set<pair<int, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
    return d;
}
*/

vector<int> dijkstra(int s, vector<vector<pair<int,int>>> adj) { // densos O(n²)
    int n = adj.size();
    vector<int> d(n+1,INF);
    vector<int> p(n+1, -1);
    vector<bool> u(n+1, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
    return d;
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
    if(actual!=INF){
        cout << actual << endl;
    }else{
        cout << -1 << endl;
    }
    }
    return 0;
}
/*
1
4 0 1 1 4
1 4 1



3
4 5 3 1 4
1 2 13
2 3 19
3 1 25
3 4 17
4 1 18
1 3 23
2 3 5
2 4 25
2 0 0 1 2
4 5 3 1 4
1 2 13
2 3 19
3 1 25
3 4 17
4 1 18
1 3 23
2 3 5
2 4 25
*/
//1 2 0 0 1 2