#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m;

void _debug(pair<int,int>* cost, vector<pair<int,pair<int,int> > > special){
    cout << "cost:\n";
    for (int i = 1; i <= n; ++i)
            cout << cost[i].first<<","<<cost[i].second<<'\n';
    cout << "special:\n";
    for (auto s:special){
        cout << s.first << " ("<<s.second.first<<","<<s.second.second<<")\n";
    }
    cout << "\n";
}

int _find(int parent[],int i){
    if (parent[i] == -1)
        return i;
    return _find(parent, parent[i]);
}

void MST(pair<int,int>* cost, vector<pair<int,pair<int,int> > > special){
    int ans = 0;
    int* parent = new int[n+1];
    int* degree = new int[n+1];
    fill(parent+1, parent+n+1, -1);
    fill(degree+1, degree+n+1, 0);
    
    int times = 0, k = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = i+1; j <= n; ++j){ 
            int src = cost[i].second, x;
            int des = cost[j].second, y;
            int weight = cost[i].first + cost[j].first;
            if (k < special.size() && special[k].first < weight){
                src = special[k].second.first;
                des = special[k].second.second;
                weight = special[k].first;
                k++;
                j--;
            }
            x = _find(parent, src);
            y = _find(parent, des);
            if (x != y){
                times++;
                ans += weight;
                if (degree[x] > degree[y]){
                    parent[y] = x;
                    degree[x]++;
                }
                else {
                    parent[x] = y;
                    degree[y]++;
                }
            }
            if (times == n-1)
                break;
        }
    }
    delete parent;
    delete degree;
    cout << ans << "\n";
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int T;
    cin>>T;
    while (T--){
        cin>>n>>m;
        pair<int, int>* cost = new pair<int, int>[n+1];
        vector<pair<int, pair<int,int> > > special;
        for (int i = 1; i <= n; ++i){
            int c;
            cin>>c;
            cost[i] = make_pair(c, i);
        }
        sort(cost+1, cost+n+1);
        special.reserve(m);
        for (int i = 0; i < m; ++i){
            int u,v,w;
            cin>>u>>v>>w;
            if (u > v)
                swap(u,v);
            special.push_back({w,{u,v}});
        }
        sort(special.begin(), special.end());
        // _debug(cost, special);
        MST(cost, special);
    }
}