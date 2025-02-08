#include <iostream>

using namespace std;

const int N = 12;

int n;
char board[N][N];
bool cols[N], dig[N<<1], adig[N<<1];

/*  n = 3
dig[]: col - row = [-2, 2], so add n=3 would be [1, 5]   <=>   y = x + b, that is b = y - x
    __________   __________   __________   __________   __________  
    |_*|__|__|   |__|_*|__|   |__|__|_*|   |__|__|__|   |__|__|__|  
    |__|_*|__|   |__|__|_*|   |__|__|__|   |__|__|__|   |_*|__|__|  
    |__|__|_*|   |__|__|__|   |__|__|__|   |_*|__|__|   |__|_*|__|  
      [0+3=3]      [1+3=4]      [2+3=5]     [-2+3=1]     [-1+3=2]   
    
adig[]: col + row = [0, 4]  <=>  y = -x + b, that is b = y + x
    __________   __________   __________   __________   __________   
    |_*|__|__|   |__|_*|__|   |__|__|_*|   |__|__|__|   |__|__|__|   
    |__|__|__|   |_*|__|__|   |__|_*|__|   |__|__|_*|   |__|__|__|   
    |__|__|__|   |__|__|__|   |_*|__|__|   |__|_*|__|   |__|__|_*|   
        [0]          [1]          [2]          [3]          [4]
*/

void dfs(int row) {
    if (row == n) {
        for (int i = 0; i < n; ++i) puts(board[i]);
        puts("");
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols[col] || dig[col - row + n] || adig[col + row]) continue;
        board[row][col] = 'Q';
        cols[col] = dig[col - row + n] = adig[col + row] = 1;
        dfs(row+1);
        cols[col] = dig[col - row + n] = adig[col + row] = 0;
        board[row][col] = '.';
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            board[i][j] = '.';
    dfs(0);
    return 0;
}