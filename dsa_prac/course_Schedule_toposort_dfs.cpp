#include<bits/stdc++.h>
using namespace std;

bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack, vector<int> adj[]) {
    visited[v] = true;
    recStack[v] = true;
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            if (isCyclicUtil(neighbor, visited, recStack, adj))
                return true;
        } else if (recStack[neighbor]) {
            return true;
        }
    }
    recStack[v] = false; 
    return false;
}

bool icanFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> adj[numCourses];
    for (const auto& prereq : prerequisites) {
        adj[prereq[1]].push_back(prereq[0]);
    }
    
    vector<bool> visited(numCourses, false);
    vector<bool> recStack(numCourses, false);
    
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, visited, recStack, adj))
                return false;
        }
    }
    return true;
}

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    
    if (icanFinish(numCourses, prerequisites)) {
        cout << "All courses can be finished." << endl;
    } else {
        cout << "Not all courses can be finished." << endl;
    }
    
    return 0;
}