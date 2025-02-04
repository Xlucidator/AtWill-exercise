#include <iostream>

using namespace std;

const int MAXN = 1e5 + 2, MAXM = 1e6 + 2;

int N, M;
char P[MAXN], S[MAXM];
int nxt[MAXN];

int main() {
    scanf("%d%s%d%s", &N, P+1, &M, S+1);

    int j;

    // build next
    nxt[1] = 0; j = 0;
    for (int i = 2; i <= N; ++i) {
        while (j != 0 && P[j+1] != P[i]) j = nxt[j];
        if (P[j+1] == P[i]) j++;
        nxt[i] = j;
    }

    // match string
    j = 0;
    for (int i = 1; i <= M; ++i) {
        while (j != 0 && P[j+1] != S[i]) j = nxt[j];
        if (P[j+1] == S[i]) j++;
        if (j == N) { // match
            printf("%d ", i - N);
            j = nxt[j];
        }
    }
    puts("");

    return 0;
}