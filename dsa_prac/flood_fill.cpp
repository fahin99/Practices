#include<bits/stdc++.h>
using namespace std;

void dfs(int x, int y, vector<vector<int>> &image, int newColor, int originalColor) {
    if(x < 0 || x >= image.size() || y < 0 || y >= image[0].size() || image[x][y] != originalColor) {
        return;
    }
    image[x][y] = newColor;
    dfs(x + 1, y, image, newColor, originalColor);
    dfs(x - 1, y, image, newColor, originalColor);
    dfs(x, y + 1, image, newColor, originalColor);
    dfs(x, y - 1, image, newColor, originalColor);
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int originalColor = image[sr][sc];
    if(originalColor != newColor) {
        dfs(sr, sc, image, newColor, originalColor);
    }
    return image;
}

int main() {
    vector<vector<int>> image = {{1,1,1},{1,1,0},{1,0,1}};
    int sr = 1, sc = 1, newColor = 2;
    vector<vector<int>> result = floodFill(image, sr, sc, newColor);
    for(const auto& row : result) {
        for(int color : row) {
            cout << color << " ";
        }
        cout << endl;
    }
    return 0;
}