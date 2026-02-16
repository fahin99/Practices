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
    void addEdge(int v, int w){
        adj[v].push_back(w);
    }
    void bfs(int src, vector<bool> &visited){
        queue<int>q;
        q.push(src);
        visited[src] = true;
        while(!q.empty()){
            int curr=q.front();
            q.pop();
            cout << curr << " ";
            for(auto i: adj[curr]){
                if(!visited[i]){
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
    bool isCycleBFS(int src, vector<bool> &visited, int parent){
        queue<pair<int, int>> q;
        q.push({src, -1});
        visited[src] = true;
        while(!q.empty()){
            int curr = q.front().first;
            int par = q.front().second;
            q.pop();
            for(auto i: adj[curr]){
                if(!visited[i]){
                    visited[i] = true;
                    q.push({i, curr});
                }
                else if(i != par) return true;
            }
        }
        return false;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    vector<bool> visited(5, false);
    g.bfs(0, visited);
    cout << "\nIs there a cycle? " << (g.isCycleBFS(0, visited, -1) ? "Yes" : "No") << endl;
}