#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m, k;
    cin>>n>>m>>k;
    int connected = 0;
    vector<int> monsters(m+1);
    for (int i = 0; i < n; ++i){
        int mon;
        cin>>mon;
        for (int j = 0; j < mon; ++j){
            int idx;
            cin>>idx;
            if (monsters[idx] == 0)
                connected++;
            monsters[idx]++;
        }
    }
    if (connected > n + k) cout << n+k <<"\n";
    else cout << connected << "\n";
}