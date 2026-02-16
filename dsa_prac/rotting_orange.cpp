#include<bits/stdc++.h>
using namespace std;

void bfs(queue<pair<int, int>> &q, vector<vector<int>> &grid, int &freshCount) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for(auto [dx, dy] : directions) {
            int newX = x + dx;
            int newY = y + dy;
            
            if(newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == 1) {
                grid[newX][newY] = 2; // Mark as rotten
                freshCount--;
                q.push({newX, newY});
            }
        }
    }
}

int orangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    queue<pair<int, int>> q;
    int freshCount = 0;
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] == 2) {
                q.push({i, j});
            } else if(grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    
    if(freshCount == 0) return 0; // No fresh oranges
    
    int minutes = -1; // Start at -1 because the first round is not a minute
    while(!q.empty()) {
        bfs(q, grid, freshCount);
        minutes++;
    }
    
    return freshCount == 0 ? minutes : -1; // If there are still fresh oranges, return -1
}

int main() {
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    int result = orangesRotting(grid);
    cout << "Minutes until all oranges are rotten: " << result << endl;
    return 0;
}