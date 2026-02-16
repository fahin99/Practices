#include<bits/stdc++.h>
using namespace std;
class Graph{
    int V;
    list<int> *adj;
public:
    Graph(int V){
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void topologicalSort(){
        vector<int> inDegree(V, 0);
        for(int i = 0; i < V; i++){
            for(auto j : adj[i]){
                inDegree[j]++;
            }
        }
        queue<int> q;
        for(int i = 0; i < V; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        //bfs
        vector<int> result;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            result.push_back(u);
            for(auto v : adj[u]){
                inDegree[v]--;
                if(inDegree[v] == 0){
                    q.push(v);
                }
            }
        }
        if(result.size() != V){
            cout << "There is a cycle in the graph" << endl;
        } else {
            for(auto i : result){
                cout << i << " ";
            }
            cout << endl;
        }
    }
};

int main(){
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    cout << "Topological Sort: ";
    g.topologicalSort();
    return 0;
}