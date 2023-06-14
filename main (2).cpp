#include <bits/stdc++.h>
#include <cmath>

using namespace std;

using ll = double;
const ll inf = 1e18;
ll sumaU;
ll sumaV;

int n,r,w,U,V,casos,k;
vector<tuple<ll,int,int>> E;

ll dist(pair<int,int> a, pair<int,int> b){
    return sqrt(pow(a.first-b.first,2)+pow(a.second-b.second,2));
}

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal(){
    sort(E.begin(),E.end());
    ll res = 0;
    int aristas = 0;
    DSU dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            if(c<=r){
                sumaU+=U*c;
            }else{
                sumaV+=V*c;
            }
            dsu.unite(u,v);
            aristas++;
            if(n-aristas==w){
                cout << "Caso #" << k << ": " << fixed << setprecision(3) << sumaU << " " << sumaV << endl;
                k++;
            }
            res += c;
        }
    }
    //if(aristas == n-1) cout<<res<<endl;
    //else cout<<"IMPOSSIBLE\n";
}

int main() {
    cin>>casos;
    k=1;
    while(casos>0){
        cin>>n>>r>>w>>U>>V;
        vector<pair<int,int>> posiciones(n,{0,0});
        sumaV=0;
        sumaU=0;
        E.clear();
        for(int i=0;i<n;i++){
            cin >> posiciones[i].first;
            cin >> posiciones[i].second;
        }

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                ll c;
                c = dist(posiciones[i],posiciones[j]);
                E.push_back({c,i,j});
            }
        }
        kruskal();
        casos--;
    }

    return 0;
}