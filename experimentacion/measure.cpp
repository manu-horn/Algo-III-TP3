#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <set>

using namespace std;
using namespace std;
int casos, n, m, k, s, t;
const int  INF = 1e18;
vector<vector<pair<int,int>>> adj;
vector<vector<pair<int,int>>> adj_inv;
vector<tuple<int,int,int>> candidatas;

/*
vector<int> dijkstra(int x, vector<vector<pair<int,int>>>& adj){    // priority queue
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
*/

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

void read_input(int size) {

    string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);

    read_file >> casos;

    for (int i = 0; i < casos; i++) {
        read_file >> n;
        read_file >> m;
        read_file >> k;
        read_file >> s;
        read_file >> t;
        adj.clear();
        adj.resize(n + 1);
        adj_inv.clear();
        adj_inv.resize(n + 1);
        for (int j = 0; j < m; j++) {
            int d, c, l;
            read_file >> d;
            read_file >> c;
            read_file >> l;
            adj[d].push_back({c, l});
            adj_inv[c].push_back({d, l});
        }
        candidatas.clear();
        for (int j = 0; j < k; j++) {
            int u, v, q;
            read_file >> u;
            read_file >> v;
            read_file >> q;
            candidatas.push_back({u, v, q});
        }
    }

        read_file.close();
}

double measure(int size) {
    auto start = chrono::high_resolution_clock::now();

        vector<int> distS = dijkstra(s, adj);
        vector<int> distT = dijkstra(t, adj_inv);
        int actual = distS[t];

        for(int i=0;i<k;i++){
            vector<tuple<int,int,int>> hola = candidatas;
            actual = min(actual, distS[get<0>(candidatas[i])] + get<2>(candidatas[i]) + distT[get<1>(candidatas[i])]);
            actual = min(actual, distS[get<1>(candidatas[i])] + get<2>(candidatas[i]) + distT[get<0>(candidatas[i])]);
        }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 10;
    ofstream output_file; output_file.open("runtime_aristas_set.csv");  //ir cambiando esto
    output_file << "n,time\n";
    
    int limit = 1<<27;
    for (int n=500; n<499500; n+=55444) {
    //for (int n=100; n<1001; n+=100) {
        //vector<int> input = read_input(n);
        read_input(n);
        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(n);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
