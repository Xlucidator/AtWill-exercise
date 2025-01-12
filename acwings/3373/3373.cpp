#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void printVec(const vector<uint8_t>& vec, const char* name) {
    printf("[vector %s] ", name);
    for (auto i : vec) printf("%d ", i);
    putchar('\n');
}

uint8_t divide(const vector<uint8_t>& divident, vector<uint8_t>& quotient) { // return remainder
    // divider is 2
    quotient.clear();
    uint8_t value = 0;
    bool msb_write = false;
    for (int i = 0; i < divident.size(); ++i) {
        value = value * 10 + divident[i];
        if (msb_write || value > 1) {
            msb_write = true;
            quotient.push_back(value >> 1);
            value &= 1;
        }
    }
    return value; // remainder
}

int main() {
    string line;
    vector<uint8_t> vec[2];

    while (getline(cin, line)) {
        /* Use Vector */
        vec[0].clear();
        transform(line.begin(), line.end(), back_inserter(vec[0]), [](char ch){
            return ch - '0';
        });
        
        /* Calculate */
        string bin_str;
        bool div = 0;
        while (true) {
            const vector<uint8_t>& divident = vec[div];
            vector<uint8_t>& quotient = vec[!div];
            bin_str += divide(divident, quotient) + '0';
            div = !div;
            if (quotient.size() == 0) break;
        }
        reverse(bin_str.begin(), bin_str.end());
        cout << bin_str << endl;
    }

    return 0;
}