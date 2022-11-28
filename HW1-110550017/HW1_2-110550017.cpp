#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class device{
    public:
    int infTime;
    int id;
    device(int t, int i):infTime(t), id(i){}
};
int main(){
    ios_base::sync_with_stdio(false);
    int n, m, k, t;
    cin>>n>>m>>k>>t;
    vector<bool> infected(n, false);
    vector<vector<int>> route(n);
    queue<device> q;
    int time = 1;
    int ans = 0;
    for (int i = 0; i < m; ++i){
        int v1, v2;
        cin>>v1>>v2;
        route[v1-1].push_back(v2-1);
    }
    for (int i = 0; i < k; ++i){
        int infected_idx;
        cin>>infected_idx;
        infected[infected_idx-1] = true;
        device d(0, infected_idx-1);
        q.push(d);
    }
    while (!q.empty()){
        if (time < t){
            for (int i = 0; i < route[q.front().id].size(); ++i){
                if (!infected[route[q.front().id][i]]){
                    device d(q.front().infTime+1, route[q.front().id][i]);
                    q.push(d);
                    infected[route[q.front().id][i]] = true;
                }
            }
        }
        time = q.front().infTime+2;
        q.pop();
    }
    for (auto a : infected){
        if (a)
            ans++;
    }
    cout << ans << "\n";
}