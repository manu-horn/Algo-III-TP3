#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> S;

vector<vector<int>> aristas = {{1,2,3,4,5,6,7},{2},{3},{1},{5,6}, {6}, {}, {}};
vector<vector<int>> aristasNuevo;
vector<vector<int>> masterGrafo;

vector<int> cfc;

vector<bool> visitado = {0,0,0,0,0,0,0,0};
int no_lo_vi = 0, empece_a_ver = 1, termine_de_ver = 2;
vector<int> estado = {0,0,0,0,0,0,0,0};

vector<vector<int>> treeEdges = {{},{},{},{},{},{},{},{}};

vector<int> backConExtremoInferiorEn = {0,0,0,0,0,0,0,0};
vector<int> backConExtremoSuperiorEn = {0,0,0,0,0,0,0,0};

int dfs(int v, vector<int>& padres, vector<vector<int>>& treeEdges, int raiz){
    int res = 0;
    estado[v] = empece_a_ver;
    for(int u : aristas[v]){
        if(!estado[u]) {
            res++;
            treeEdges[v].push_back(u);
            padres[u] = v;
            res += dfs(u, padres, treeEdges, raiz);
        } else if (u != padres[v] && estado[u]== empece_a_ver){
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
        if(!visitado[u]){
            visitado[u]=true;
            cfc[u]=raiz;
        }else if (cfc[u]!=cfc[v]){
            masterGrafo[u].push_back(v);
        }


    }
    estado[v] = termine_de_ver;
    S.push(v);
    return res;
}

vector<int> memo(8,-1);

int cubren(int v, vector<int>& padres,vector<vector<int>>& treeEdges){
    vector<int> b = memo;
    if(memo[v] != -1) return memo[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];

    for(int hijo : treeEdges[v]){
        if(hijo != padres[v]){
            res += cubren(hijo,padres, treeEdges);
        }
    }

    memo[v] = res;
    return res;
}


void print(vector<int> a){
    for(auto i : a){
        cout << i;
    }
    cout << endl;
}


int main() {
    int n = 7;
    vector<int> componentes(n+1,0);
    cfc.resize(n+1,0);
    masterGrafo.resize(n+1);

    vector<int> padres(n+1,0);
    vector<vector<int>> treeEdges = {{},{},{},{},{},{},{},{}};

    int cantComponentes = 0;

    for (int i =1; i<n+1;i++){
        if(!visitado[i]){
            visitado[i]=true;
            componentes[i] = 1+ dfs(i,padres, treeEdges, i);
            cantComponentes++;
        }
    }


    for(int i=1;i<componentes.size();i++){      //CUBREN NUEVO
        if(componentes[i]!=0){
            cubren(i,padres,treeEdges);
        }
    }
    //cubren(1,padres,treeEdges); // cubre: (sup,inf]  VIEJO
    int puentes = 0;

    for (int i=1; i<n+1;i++){
        if (memo[i] == 0){
            puentes++;
        }
    }

    aristasNuevo.resize(n+1);
    for(int i=1;i<aristas.size();i++){
        for(int j=0;j<aristas[i].size();j++){
            aristasNuevo[aristas[i][j]].push_back(i);
        }
    }

    for(int i=1;i<=n;i++){
        aristasNuevo[0].push_back(i);
    }
    vector<vector<int>> H = aristasNuevo;

    estado = {0,0,0,0,0,0,0,0};
    visitado = {0,0,0,0,0,0,0,0};

    cfc.resize(n+1,0);
    aristas.clear();
    aristas=aristasNuevo;
    masterGrafo.clear();
    masterGrafo.resize(n+1);

    while (!S.empty()){
        int i = S.top();
        S.pop();
        if(!visitado[i]){
            visitado[i]=true;
            cfc[i]=i;
            dfs(i,padres, treeEdges, i);
            cantComponentes++;

        }
    }



    vector<int> comp = cfc;


    for(int i=1;i<cfc.size();i++){

        masterGrafo[0].push_back(cfc[i]);
        while(i<=n-2 && cfc[i+1]==cfc[i]){
            i++;
        }

    }

    vector<vector<int>> master = masterGrafo;
    aristas.clear();
    aristas = masterGrafo;
    estado = {0,0,0,0,0,0,0,0};
    visitado = {0,0,0,0,0,0,0,0};
    componentes.clear();
    componentes.resize(n+1,0);
    cantComponentes=0;
    padres.resize(n+1,0);

    for (int i =1; i<n+1;i++){
        if(!visitado[i] && cfc[i]==i){
            visitado[i]=true;
            componentes[i] = 1+ dfs(i,padres, treeEdges, i);
            cantComponentes++;
        }
    }



    vector<int> res;
    stack<int> J = S;
    while(!S.empty()){
        //res.push_back(S.top());
        S.pop();
    }


    for(int i=1;i<padres.size();i++){
        if(padres[i]==0){
            res.push_back(i);
        }
    }

    cout << res.size() << endl;
    for(int i=0;i<res.size();i++){
        cout << res[i] << " ";
    }


    return 0;
}
