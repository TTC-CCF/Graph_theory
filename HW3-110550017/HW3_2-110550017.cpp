#include<bits/stdc++.h>
#define int long long
#define MAX LLONG_MAX
using namespace std;

int* Dijkstra(vector<vector<pair<int,int> > > RM, int src, int n){
    priority_queue<pair<int,int> > pq;
        int* dis = new int[n];
        fill(dis,dis+n,MAX);
        dis[src] = 0;
        for (auto v:RM[src]){
            pq.push({-v.second, v.first});
            dis[v.first] = min(dis[v.first], v.second);
        }
        while(pq.size()){
            int cur = pq.top().second;
            pq.pop();
            for (auto v:RM[cur]){
                if (dis[v.first] > v.second+dis[cur]){
                    dis[v.first] = v.second+dis[cur];
                    pq.push({-dis[v.first], v.first});
                }
            }
        }
        for (int i = 1; i < n; ++i){
            if (dis[i] == MAX)
                dis[i] = -1;
        }
    return dis;
}

void solve(){
    int res,road,waku;
    cin>>res>>road>>waku;
    vector<vector<pair<int,int> > > RM(res+1);
    int* ans = NULL;
    for (int i = 0; i < road; ++i){
        int u,v,w;
        cin>>u>>v>>w;
        RM[v].push_back({u,w});
    }
    if (waku == 1){
        ans = Dijkstra(RM, 1, res+1);
    }
    else if (waku == 2){
        int* dis1 = Dijkstra(RM, 1, res+1);
        int* dis2 = Dijkstra(RM, res, res+1);
        RM.push_back(vector<pair<int,int> >(0));
        for (int i = 1; i <= res; ++i){
            if (dis1[i] == -1 || dis2[i] == -1){
                continue;
            }
            int nw = dis1[i] + dis2[i];
            RM[res+1].push_back({i,nw});
        }
        ans = Dijkstra(RM, res+1, res+2);
    }
    for (int i = 1; i <= res; ++i){
        if (i == res)
            cout << ans[i] << "\n";
        else
            cout << ans[i] << " ";
    }
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int T, sub;
    cin>> T >> sub;
    while(T--){
        solve();
    }
    return 0;
}