#include<iostream>
#include<vector>
using namespace std;
void printGraph(vector<vector<int>> graph, int n);
int main(){
    int n, m;
    cin>>n>>m;
    vector<vector<int>>graph(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        graph[v1-1][v2-1] = w;
    }
    printGraph(graph, n);
    for (int i = 0; i < n; ++i){
        int indegree=0, outdegree=0;
        for (int j = 0; j < n; ++j){
            if (graph[j][i] != 0)
                indegree++;
            if (graph[i][j] != 0)
                outdegree++;
        }
        cout << indegree << " " << outdegree << "\n";
    }


}
void printGraph(vector<vector<int>> graph, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cout << graph[i][j] << " ";
        }
        puts(" ");
    }
}