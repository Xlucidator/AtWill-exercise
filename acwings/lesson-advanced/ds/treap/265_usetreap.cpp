#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 33000 + 10;

int n;
struct Node {
    int l, r;
    int key, val;
} tr[N];