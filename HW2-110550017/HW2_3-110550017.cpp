#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> graph;
vector<int> key;
vector<int> degree;
vector<int> _count;
vector<int> _visit;
vector<int> outer_j;
int32_t main(){
    cin>>n;
    graph.resize(n);
    degree.resize(n);
    _count.resize(n, 0);
    _visit.resize(n, 0);
    for (int i = 0; i < n-1; ++i){
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
        degree[v]++;
        degree[u]++;
    }
    queue<int> q;
    for (int i = 0; i < n; ++i){
        if (degree[i] == 1){
            _visit[i] = 1;
            _count[i] = 1;
            q.push(i);
        }
        else if (degree[i] == 3){
            _visit[i] = 2;
        }
    }
    while (!q.empty()){
        int k = q.front();
        q.pop();
        for (auto a : graph[k]){
            if (_visit[a] != 1){
                degree[a]--;
                degree[k]--;
                if (_visit[a] == 0 && degree[a] == 1){
                    _count[a] = _count[k]+1;
                    _visit[a] = 1;
                    q.push(a);
                }
            }
        }
    }
    // for (auto i : degree) cout << i << " ";
    cin>>m;
    key.resize(m);
    for (int i = 0; i < m; ++i) cin >> key[i];
    for (int i = 0; i < n; ++i){
        if (_visit[i] == 2 && degree[i] <= 1){
            outer_j.push_back(i);
        }
    }
    if (outer_j.size() == 1){
        if (m != 1){
            cout << "NO\n";
        }
        else{
            bool fg = 1;
            for (int v : graph[outer_j[0]]){
                if (key[0] == _count[v]){
                    cout << "YES\n";
                    fg = 0;
                    break;
                }
            }
            if (fg)
                cout << "NO\n";
        }
    }
    else{
        for (int i = 0; i < 2; ++i){
            vector<int> possible;
            q.push(outer_j[i]);
            int done = -1;
            while (!q.empty()){
                int k = q.front();
                q.pop();
                for (auto v : graph[k]){
                    if (_count[v] != 0)
                        possible.push_back(_count[v]);
                    else if (v != done && _visit[v] != 1)
                        q.push(v); 
                }
                done = k;
            }
            bool fg = 1;
            // for (int j : possible) cout << j << " ";
            // cout << "\n";
            if (possible.size() != m+2){
                cout << "NO\n";
                break;
            }
            else{

                if (possible[0] == key[0] || possible[1] == key[0]){
                    for (int i = 2; i < m; ++i){
                        if (key[i - 1] != possible[i]){
                            fg = 0;
                        }
                    }
                    if (fg && (key[m-1] != possible[m] && key[m-1] != possible[m+1]))
                        fg = 0;
                }
                else
                    fg = 0;
                if (fg){
                    cout << "YES\n";
                    break;
                }
            }
            if (i == 1 && !fg)
                cout << "NO\n";
        }
    }
    return 0;
    
}