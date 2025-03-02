#include <iostream>
#include <string>

using namespace std;

const int N = 1e5 + 2;

typedef long long ll;

int n, m;

int main() {
    string str;
    cin >> n >> m >> str;

    int cnt = 0; ll total = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '1') {
            cnt++;
        } else {
            for (int v = cnt - m + 1; v >=1; --v) total += v;
            cnt = 0;
            // printf("total = %d\n", total);
        }
    }
    for (int v = cnt - m + 1; v >=1; --v) total += v;
    cout << total << endl;

    return 0;
}