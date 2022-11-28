#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxx = 1000002;
int* height = new int[maxx];
int* parent = new int[maxx];
int dfs(vector<vector<int> > &T, int v){     // 如果不用pass by reference 就會一直累積memory, 會很慢又很腫
    if (T[v].size()>1 || v == 1){
        for (int n : T[v]){
            if (parent[v] != n){
                parent[n] = v;
                height[v] = max(dfs(T, n)+1, height[v]);
            }
        }
        return height[v];
    }
    else{
        return 0;
    }
}
int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int V;
    cin>>V;
    vector<vector<int>> T(V+1);
    for (int i = 0; i < V-1; ++i){
        int u, v;
        cin>>u>>v;
        T[u].push_back(v);
        T[v].push_back(u);
    }
    fill(height+1, height+V+1, 0);
    fill(parent+1, parent+V+1, -1);
    dfs(T, 1);
    for (int i = 1; i <= V; ++i){
        cout << height[i] << " " << parent[i]<<"\n";
    }
    delete height;
    delete parent;
    return 0;
}