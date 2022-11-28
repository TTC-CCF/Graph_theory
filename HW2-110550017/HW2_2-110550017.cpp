#include<bits/stdc++.h>
// #define int long long
using namespace std;
vector<vector<int>> graph;
vector<int> _visit;
vector<pair<int, int>> walk;
vector<vector<int>> table;
void dfs(int level, int v){
    walk.push_back({v, level});
    _visit[v] = 1;
    for (int i : graph[v]){
        if (_visit[i] == 0){
            dfs(level+1, i);
            walk.push_back({v, level});
        }
    }
}
void buildTable(){
    int n = walk.size();
    int j = (int)ceil(log2(n));
    for (int i = 0; i < n; ++i){
        if (_visit[walk[i].first] == -1){
            _visit[walk[i].first] = i;
        }
    }
    table.resize(n, vector<int>(j, -1));
    for (int i = 0; i < n; ++i){
        table[i][0] = i;
    }     
    for (int j = 1; (1 << j) < n; ++j){
        for (int i = 0; i + (1 << j)-1 < n; ++i){
            if (walk[table[i][j-1]].second <= walk[table[i + (1<<(j-1))][j-1]].second){
                table[i][j] = table[i][j-1];
            }
            else{
                table[i][j] = table[i +(1<<(j-1))][j-1];
            }
        }
    }
}
void query(int v, int u){
    int l, r, j;
    l = _visit[v];
    r = _visit[u];
    if (l > r) swap(l, r);
    j = (int)floor(log2(r-l+1));
    int lca = min(walk[table[l][j]].second, walk[table[r-(1<<j)+1][j]].second);
    cout << walk[l].second + walk[r].second - 2*lca << "\n";

}
int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n, q;
    cin >> n;
    graph.resize(n);
    _visit.resize(n, 0);
    for (int i = 0; i < n-1; ++i){
        int v, u;
        cin >> v >> u;
        graph[v-1].push_back(u-1);
        graph[u-1].push_back(v-1);
    }
    dfs(0, 0);
    _visit.clear();
    _visit.resize(n, -1);
    buildTable();
    cin >> q;
    for (int i = 0; i < q; ++i){
        int v, u;
        cin >> v >> u;
        query(v-1, u-1);
    }
}