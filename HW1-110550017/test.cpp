#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define int long long

bool solve(vector<int> ds){
    sort(ds.begin()+1, ds.end(), greater<int>());
    
    int n = ds.size()-1;
    if (ds[n] < 0) return false;
    vector<int> sums(n+1);
    sums[1] = ds[1];
    for (int i = 2; i <= n; ++i){
        sums[i] = sums[i-1] + ds[i];
        if (sums[i] < sums[i-1])
            return false;
    }
    if (sums[n]%2 == 1) return false;

    int w = n;
    for (int i = 1; i <= n; ++i){
        while (w-- && ds[w] < i);
        int y = max(i, w);
        if (sums[i] > i*(y-1) + sums[n] - sums[y])
            return false;
    }
    return true;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    int Q;
    cin >> Q;
    while (Q--){
        int n, m;
        cin >> n >> m;
        vector<int> ds(n+1);
        for (int i = 1; i <= n; ++i){
            cin >> ds[i];
        }
        for (int i = 0; i < m; ++i){
            int u, v;
            cin >> u >> v;
            ds[u]--;
            ds[v]--;
        }
        if (solve(ds))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}