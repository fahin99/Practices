#include <bits/stdc++.h>
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
    // void dfs(int src, vector<bool> &visited){
    //     visited[src] = true;
    //     cout << src << " ";
    //     for(auto i : adj[src]){
    //         if(!visited[i]){
    //             dfs(i, visited);
    //         }
    //     }
    // }
    void dfs(int src, vector<bool> &visited){
        stack<int> s;
        s.push(src);
        while(!s.empty()){
            int curr = s.top();
            s.pop();
            if(!visited[curr]){
                visited[curr] = true;
                cout << curr << " ";
                for(auto i : adj[curr]){
                    if(!visited[i]){
                        s.push(i);
                    }
                }
            }
        }
    }
    bool isCycle(int src, vector<bool> &visited, int parent){
        visited[src] = true;
        for(auto v: adj[src]){
            if(!visited[v]){
                if(isCycle(v, visited, src)) return true;
            }
            else if(v!= parent) return true;
        }
        return false;
    }
    bool isCycleDirectedGraph(int src, vector<bool> &visited, vector<bool> &recStack){
        visited[src] = true;
        recStack[src] = true;
        for(auto v: adj[src]){
            if(!visited[v]){
                if(isCycleDirectedGraph(v, visited, recStack)) return true;
            }
            else if(recStack[v]) return true;
        }
        recStack[src] = false;
        return false;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    // g.addEdge(2, 4);
    vector<bool> visited(5, false);
    cout << "DFS starting from vertex 0: ";
    g.dfs(0, visited);
    // cout << "\nIs there a cycle? " << (g.isCycle(0, visited, -1) ? "Yes" : "No") << endl;
    return 0;
}

