#include <iostream>

using namespace std;

const int N = 1e5 + 2;

int n, m;
int s[N];

int main() {
    cin >> n >> m;
    
    int a;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        s[i] = s[i-1] + a;
    }
    
    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << s[r] - s[l-1] << endl;
    }
    
    return 0;
}