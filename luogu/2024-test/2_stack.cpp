#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 10;  // 2e5+10
typedef long long ll;

int n, m;

struct Stack {
    vector<ll> num_prefix = {0};
    vector<ll> cnt_prefix = {0};
    // vector<int> single = {0};

    void resize(int i) {
        num_prefix.resize(i);
        cnt_prefix.resize(i);
        // single.resize(i);
    }
    size_t size() { return cnt_prefix.size(); }
    // void clear() {
    //     num_prefix.clear();
    //     cnt_prefix.clear();
    //     single.clear();
    // }
    void print(int idx) {
        printf("[stack %d]\n", idx);
        for (int i = 0; i < size(); ++i) printf(" [%2d] ", i); puts("");
        for (auto item : num_prefix) printf("%5lld ", item); puts("");
        for (auto item : cnt_prefix) printf("%5lld ", item); puts("");
        // for (auto item : single) printf("%5d ", item); puts("");
    }
} st[N];



void push(int x, int w, ll cnt) {
    Stack& tar = st[x];
    auto& num_ps = st[x].num_prefix; auto& cnt_ps = st[x].cnt_prefix;

    int i = num_ps.size() - 1;
    if (i > 0) {
        ll single = (num_ps[i] - num_ps[i-1]) / (cnt_ps[i] - cnt_ps[i-1]);
        if (single == w) {
            num_ps.back() += w * cnt;
            cnt_ps.back() += cnt;
            printf("%lld\n", num_ps.back());
            return;
        }
    }
    
    ll x_sum = num_ps.back() + w * cnt;
    num_ps.push_back(x_sum);
    cnt_ps.push_back(cnt_ps.back() + cnt);
    // tar.single.push_back(w);
    // tar.print(x);
    printf("%lld\n", x_sum);
}

void pop(int x, ll cnt) {
    Stack& tar = st[x];
    auto& num_ps = tar.num_prefix; auto& cnt_ps = tar.cnt_prefix; //auto& sg = tar.single;

    ll r_sum = num_ps.back(), l_sum;
    ll l_cnt = cnt_ps.back() - cnt;
    auto it = upper_bound(cnt_ps.begin(), cnt_ps.end(), l_cnt); it--;
    int i = it - cnt_ps.begin();

    // printf("[pop debug] i = %d\n", i);

    ll exceed_cnt = l_cnt - *it;
    if (exceed_cnt == 0) {
        l_sum = num_ps[i];
        tar.resize(i + 1);
        // tar.print(x);
        printf("%lld\n", r_sum - l_sum);
        return;
    }

    ll single = (num_ps[i+1] - num_ps[i]) / (cnt_ps[i+1] - cnt_ps[i]);
    ll exceed_sum = exceed_cnt * single; // ll exceed_sum = exceed_cnt * sg[i+1];
    l_sum = num_ps[i] + exceed_sum;
    num_ps[i+1] = l_sum; cnt_ps[i+1] = cnt_ps[i] + exceed_cnt;
    tar.resize(i+2);
    // tar.print(x);
    printf("%lld\n", r_sum - l_sum);
}

void merge(int x, int y) {
    Stack& dst = st[y]; Stack& src = st[x];
    auto& dst_num_ps = dst.num_prefix; auto& dst_cnt_ps = dst.cnt_prefix; //auto& dst_sg = dst.single;
    auto& src_num_ps = src.num_prefix; auto& src_cnt_ps = src.cnt_prefix; //auto& src_sg = src.single;
    for (int i = src.size() - 1; i > 0; --i) {
        dst_num_ps.push_back(dst_num_ps.back() + src_num_ps[i]-src_num_ps[i-1]);
        dst_cnt_ps.push_back(dst_cnt_ps.back() + src_cnt_ps[i]-src_cnt_ps[i-1]);
        // dst_sg.push_back(src_sg[i]);
    }
    src.resize(1);
    // src.print(x);
    // dst.print(y);
    printf("%lld\n", dst_num_ps.back());
}

int main() {
    scanf("%d%d", &n, &m);

    int op;
    int x, y, w, c;
    while (m--) {
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1: {
                scanf("%d%d", &w, &c);
                push(x, w, c);
                break;
            }
            case 2: {
                scanf("%d", &c);
                pop(x, c);
                break;
            }
            case 3: {
                scanf("%d", &y);
                merge(x, y);
                break;
            }
            default: break;
        }
        
    }

    return 0;
}