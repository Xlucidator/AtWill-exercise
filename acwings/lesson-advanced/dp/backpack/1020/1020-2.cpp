#include <iostream>
#include <cstring>
using namespace std;
const int N = 1010,M = 85;
int n,m,t;
int v1[N],v2[N],w[N];
int f[M][M];
int main(){
    cin>>n>>m>>t;
    for(int i = 1;i <= t;i ++) cin>>v1[i]>>v2[i]>>w[i];

    memset(f,0x3f,sizeof f);
    f[0][0] = 0;

    for(int i = 1;i <= t;i ++){
        for(int j = n;j >= 0;j --){
            for(int k = m;k >= 0;k --){
                f[j][k] = min(f[j][k],f[max(j - v1[i],0)][max(k - v2[i],0)] + w[i]);
            }
        }
    }
    cout<<f[n][m]<<endl;
    return 0;
}
