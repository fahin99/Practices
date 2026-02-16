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
    void topoSortUtil(int src, vector<bool> &visited, stack<int> &st){
        visited[src] = true;
        for(auto i: adj[src]){
            if(!visited[i]){
                topoSortUtil(i, visited, st);
            }
        }
        st.push(src);
    }
    void topoSort(){
        vector<bool> visited(V, false);
        stack<int> st;
        for(int i=0; i<V; i++){
            if(!visited[i]){
                topoSortUtil(i, visited, st);
            }
        }
        while(!st.empty()){
            cout << st.top() << " ";
            st.pop();
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
    g.topoSort();
    return 0;
}