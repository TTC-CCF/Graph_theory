#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int> > graph;
vector<int> vis;
vector<int> par;
vector<int> ans;
int rcd = 0;
int dfs(int cur, int tn){
    int tp = INT_MAX;
    int low_c = INT_MAX;
    bool pushed = false;
    vis[cur] = tn;

    for (auto v : graph[cur]){
        if (vis[v] == -1){
            if (cur == 1) rcd++;
            par[v] = cur;
            int c = dfs(v, tn+1);
            if (!pushed){
                if (cur == 1){
                    if (rcd > 1){
                        ans.push_back(1);
                        pushed = true;
                    }
                }
                else if (c >= vis[cur]){
                    ans.push_back(cur);
                    pushed = true;
                }
                
            }
            low_c = min(low_c, c);
        }
    }
    for (auto v : graph[cur]){
        if (par[v] != cur ){
            tp = min(tp, vis[v]);
        }
    }
    
    return min(min(tp,low_c), vis[cur]);
}
int main(){
    cin>>n>>m;
    graph.resize(n+1);
    vis.resize(n+1, -1);
    par.resize(n+1, 0);
    for (int i = 0; i < m; ++i){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (n == 1){
        cout << "0\n";
        return 0;
    }
    dfs(1, 0);
    sort(ans.begin(), ans.end());
    cout << ans.size()<<"\n";
    for (int i = 0; i < ans.size(); ++i) {
        if (i == ans.size()-1) cout << ans[i] << "\n";
        else cout << ans[i] << " ";
    }
    return 0;
}