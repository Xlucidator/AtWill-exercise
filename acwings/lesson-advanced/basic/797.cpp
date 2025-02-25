#include <iostream>

using namespace std;

const int N = 1e5 + 2;
int n, m;
int a[N], b[N];

int main() { 
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) { 
        scanf("%d", &a[i]);
        b[i] = a[i] - a[i-1];
    }
    
    int l, r, c;
    while (m--) { 
        scanf("%d%d%d", &l, &r, &c);
        b[l] += c;
        b[r+1] -= c;
    }

    int sum = 0;
    for (int i = 1; i <= n; i++)
        printf("%d ", sum += b[i]);
    puts("");
    
    return 0;
}
