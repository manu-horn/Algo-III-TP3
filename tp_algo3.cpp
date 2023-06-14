#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> aristas = {{1,2,3,4},{2,3,4},{1,4},{1},{1,2}};
vector<bool> visitado = {0,0,0,0,0};

int no_lo_vi = 0, empece_a_ver = 1, termine_de_ver = 2;
vector<int> estado = {0,0,0,0,0};

vector<vector<int>> treeEdges = {{},{},{},{},{}};

vector<int> backConExtremoInferiorEn = {0,0,0,0,0};
vector<int> backConExtremoSuperiorEn = {0,0,0,0,0};

int dfs(int v, vector<int>& padres, vector<vector<int>>& treeEdges){
    int res = 0;
    estado[v] = empece_a_ver;
    for(int u : aristas[v]){
        if(!estado[u]) {
            res++;
            treeEdges[v].push_back(u);
            padres[u] = v;
            res += dfs(u, padres, treeEdges);
        } else if (u != padres[v] && estado[u]== empece_a_ver){
            //padres[u] = v;
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
        visitado[u]=true;
    }
    estado[v] = termine_de_ver;
    return res;
}

vector<int> memo(5,-1);

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


int combinatorio(int n , int k){
    vector<vector<int>> A(n+1, vector<int>(k+1, 0));
    for(int i=0; i<=n;i++){
        A[i][0]=1;
    }
    for(int j=0;j<k;j++){
        A[j][j]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=min(i,k);j++){
            A[i][j]= A[i-1][j-1]+A[i-1][j];
        }
    }
    return A[n][k];
}

int main() {
    int n = 4;
    vector<int> componentes(n+1,0);

    vector<int> padres(n+1,0);
    vector<vector<int>> treeEdges = {{},{},{},{},{}};

    int cantComponentes = 0;

    for (int i =1; i<n+1;i++){
        if(!visitado[i]){
            visitado[i]=true;
            componentes[i] = 1+ dfs(i,padres, treeEdges);
            cantComponentes++;
        }
    }


    //print(backConExtremoSuperiorEn);
    //print(backConExtremoInferiorEn);

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

    //------------------------------

    vector<vector<int>> aristas2 = aristas;
    memo[1]=1;
    vector<int> memo2 = memo;

    for(int i=0;i<aristas2.size();i++){
        if(memo[i]==0){
            for(auto it = aristas2[i].begin();it!=aristas2[i].end();it++){
                if(*it==padres[i]){
                    it = aristas2[i].erase(it);   // Tree edges que no son puente
                    --it;

                    for(auto it2 = aristas2[padres[i]].begin();it2!=aristas2[padres[i]].end();it2++){
                        if(*it2==i){
                            it2 = aristas2[padres[i]].erase(it2);   // Tree edges que no son puente
                            --it2;

                        }
                    }

                }
            }
        }
    }

    aristas = aristas2;

    vector<int> componentes2(n+1,0);

    vector<int> padres2(n+1,0);

    int cantComponentes2 = 0;

    cantComponentes = 0;
    visitado = {0,0,0,0,0};
    estado = {0,0,0,0,0};

    vector<vector<int>> treeEdgesNuevo = {{},{},{},{},{}};

    for (int i =1; i<n+1;i++){
        if(!visitado[i]){
            visitado[i]=true;
            componentes2[i] = 1+  dfs(i,padres2, treeEdgesNuevo);
            cantComponentes2++;
        }
    }
    print(componentes2);
    //print(componentes);
    cout << cantComponentes2 << endl;
    cout << combinatorio(5,2) << endl;

    int suma = 0;
    for(int i=1;i<componentes2.size();i++){
        if(componentes2[i]!=0){
            suma += combinatorio(componentes2[i],2);
        }
    }

    float res =  float(suma) / float(combinatorio(n,2));

    cout << res;


    return 0;
}
