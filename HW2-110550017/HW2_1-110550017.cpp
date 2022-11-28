#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<string> st;
vector<vector<int>> graph;
bool overlap = false;
int lengofappend(string a, string b){
    for (int i = 1; i < a.length(); ++i){
        if (a.substr(i) == b.substr(0, a.length() - i)){
            overlap = true;
            return b.length()-(a.length()-i);
        }
    }
    return b.length();
}
void buildGraph(vector<vector<int>> &g, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            g[i][j] = lengofappend(st[i], st[j]);
        }
    }
}
string TSP(int m){
    vector<vector<int>> dp((1<<m), vector<int>(m, 0)), path((1<<m), vector<int>(m, 0));
    int mini = INT_MAX;
    vector<int> swlist;
    for (int i = 1; i < (1<<m); ++i){
        dp[i].insert(dp[i].begin(), m, INT_MAX);
        for (int j = 0; j < m; ++j){
            if ((i & (1 << j)) > 0){                //判斷第j個點有沒有在set裡
                if (i - (1 << j) == 0)              //如果|set| == 1
                    dp[i][j] = st[j].length();
                else{                               //如果|set| > 1
                    for (int f = 0; f < m; ++f){
                        if (dp[i - (1 << j)][f] < INT_MAX && dp[i - (1 << j)][f] + graph[f][j] < dp[i][j]){
                            dp[i][j] = dp[i - (1 << j)][f] + graph[f][j];
                            path[i][j] = f;
                        }
                    }
                }
            }
            if (i == (1 << m) - 1){
                if(dp[i][j] < mini){
                    mini = dp[i][j];
                    swlist.clear();
                    swlist.push_back(j);
                }
                else if (dp[i][j] == mini){
                    mini = dp[i][j];
                    swlist.push_back(j);
                }
            }
        }
    }

    string ans = "-1", a, b;
                                        /* s 代表目前的集合，last代表最後一個點，
                                        要依序從1111開始找沒有last的集合的path[s][last]*/
    for (auto sw : swlist){
        string legal="";
        int s = (1 << m) -1;
        int prv = sw;
        while (s>0){
            if (legal == ""){
                legal = st[sw];
            }
            else{
                a = legal.substr(st[prv].length() - graph[sw][prv]);
                b = st[sw];
                legal = b + a;
            }
            int temp = s;
            s -= (1 << sw);
            prv = sw;
            sw = path[temp][sw];
        }
        if (ans == "-1") {ans = legal;/*cout << "legal :" <<legal << "\n";*/}
        else ans = min(ans, legal);
        //cout << legal << "\n";
    }

    return ans;
}
int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int N, n = 0;
    cin >> N;
    vector<string> S(N);
    while (N--){
        cin>>S[n++];
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (i == j) continue;
            if (S[i].find(S[j]) != string::npos){
                S[j] = "\0";
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (S[i] != "\0"){
            st.push_back(S[i]);
        }
    }
    sort(st.begin(), st.end());
    int m = st.end() - st.begin();
    graph.resize(m, vector<int>(m, 0));
    buildGraph(graph, m);
    if (overlap){
        cout << TSP(m) << "\n"; 
    }
    else{
        for (auto a : st) cout << a;
        cout << "\n";
    }
    return 0;
}
