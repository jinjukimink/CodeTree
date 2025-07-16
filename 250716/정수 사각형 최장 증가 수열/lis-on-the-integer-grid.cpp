#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> grid;
vector<vector<int>> dp;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int dfs(int x, int y) {
    if (dp[x][y] != 0) return dp[x][y];  // 이미 계산된 값이면 반환

    dp[x][y] = 1;  // 자기 자신
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] > grid[x][y]) {
            dp[x][y] = max(dp[x][y], dfs(nx, ny) + 1);
        }
    }
    return dp[x][y];
}

int main() {
    cin >> n;
    grid.assign(n, vector<int>(n));
    dp.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans = max(ans, dfs(i, j));

    cout << ans << endl;
    return 0;
}
