#include <iostream>

using namespace std;

const int MAXN = 1e5 + 2;

int N;
int s[MAXN], top;

int main() {
    cin >> N;
    int a;
    while (N--) {
        cin >> a;
        while (top/* is_empty: do not forget! */ && s[top] >= a) top--;
        cout << ((top == 0) ? -1 : s[top]) << " "; 
        s[++top] = a;
    }
    cout << endl;

    return 0;
}