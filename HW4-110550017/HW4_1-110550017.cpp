#include<bits/stdc++.h>
using namespace std;
#define nl "\n"
#define int long long
int n,m,p,q,t,T;
int num_infected;
vector<vector<pair<int,int> > > virus;
vector<vector<int> > antiv;
vector<int> infected;
vector<int> defended;
    
void dfs_v(int cur_time, int v){
    for (auto n : virus[v]){
        int u = n.first;
        int w = n.second;
        if (infected[u]==-1 && w + cur_time <= T){
            num_infected++;
            infected[u] = w+cur_time;
            dfs_v(w+cur_time, u);
        }
    }
}

void dfs_a(int cur_time, int v){
    for (auto u : antiv[v]){
        if (infected[u] >= cur_time+1 && defended[u] == -1){
            num_infected--;
            defended[u] = cur_time+1;
            dfs_a(cur_time+1, u);
        }
    }
}

int32_t main(){
    cin>>n>>m>>p>>q>>t>>T;
    num_infected = p;
    virus.resize(n+1);
    antiv.resize(n+1);
    infected.resize(n+1,-1);
    defended.resize(n+1,-1);
    for (int i =0;i < m; ++i){
        int a,b,w;
        cin>>a>>b>>w;
        virus[a].push_back({b,w});
        antiv[a].push_back(b);
    }
    for (int i = 0; i < p; ++i){
        int v;
        cin>>v;
        infected[v] = 0;
    }
    for (int i = 1; i <= n; ++i){
        if (!infected[i])
            dfs_v(0,i);
    }
    for (int i = 0; i < q; ++i){
        int v;
        cin>>v;
        if (infected[v] >= t || infected[v] == -1){
            if (infected[v] != -1) num_infected--;
            defended[v] = t;
        }
    }
    for (int i = 1; i <= n; ++i){
        if (defended[i] == t){
            dfs_a(t,i);
        }
    }
    cout << num_infected << nl;
    return 0;
}