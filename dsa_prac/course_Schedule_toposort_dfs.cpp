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

void topoSortUtil(int v, vector<bool> &visited, stack<int> &st, vector<int> adj[]) {
    visited[v] = true;
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            topoSortUtil(neighbor, visited, st, adj);
        }
    }
    st.push(v);
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> adj[numCourses];
    for (const auto& prereq : prerequisites) {
        adj[prereq[1]].push_back(prereq[0]);
    }
    
    vector<bool> visited(numCourses, false);
    vector<bool> recStack(numCourses, false);
    stack<int> topoStack;
    
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, visited, recStack, adj))
                return {}; // Return empty if there's a cycle
        }
    }
    // If no cycle, perform topological sort
    fill(visited.begin(), visited.end(), false); // Reset visited for topological sort
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            topoSortUtil(i, visited, topoStack, adj);
        }
    }
    
    vector<int> order;
    while (!topoStack.empty()) {
        order.push_back(topoStack.top());
        topoStack.pop();
    }
    
    return order;
}

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    
    if (icanFinish(numCourses, prerequisites)) {
        cout << "All courses can be finished." << endl;
    } else {
        cout << "Not all courses can be finished." << endl;
    }
    
    vector<int> order = findOrder(numCourses, prerequisites);
    cout << "Course order: ";
    for (int course : order) {
        cout << course << " ";
    }
    cout << endl;
    
    return 0;
}