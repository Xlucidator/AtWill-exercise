#include <iostream>

using namespace std;

const int MAXN = 1e5 + 2, MAXM = 1e6 + 2;

int N, M;
char P[MAXN], S[MAXM];
int nxt[MAXN];

int main() {
    scanf("%d%s%d%s", &N, P, &M, S);

    // build next
    nxt[0] = -1;
    int j = 0, t = -1;
    while (j < N-1) {
        if (t == -1 || P[j] == P[t]) { // match
            j++, t++;
            nxt[j] = t; // donot use improved
        } else { // unmatch
            t = nxt[t];
        }
    }

    // match string
    int i = 0; j = 0;
    while (i < M) {
        if (j == -1 || P[j] == S[i]) { 
            if (j == N-1) {
                printf("%d ", i-j);
                j = nxt[j];
            } else {
                i++, j++; 
            }
        }
        else j = nxt[j];
        // if (j == N) {
        //     printf("%d ", i-j);
        //     j = nxt[j-1];
        // }
    }
    puts("");

    return 0;
}