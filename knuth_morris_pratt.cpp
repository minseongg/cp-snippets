#include <iostream>
#include <string>
#include <vector>

using namespace std;

using vi = vector<int>;

vi get_pi(const string &s) {
    const auto sz = s.size();
    vi pi(sz);
    int j = 0;

    for (int i = 1; i < sz; i++) {
        while (j && s[i] != s[j]) { j = pi[j - 1]; }
        if (s[i] == s[j]) { pi[i] = ++j; }
    }

    return pi;
}

vi kmp(const string &origin, const string &target) {
    const auto osz = origin.size(), tsz = target.size();
    vi ret, pi = get_pi(target);
    int j = 0;
    
    for (int i = 0; i < osz; i++) {
        while (j && origin[i] != target[j]) { j = pi[j - 1]; }
        if (origin[i] == target[j]) {
            if (j == tsz - 1) {
                ret.emplace_back(i - tsz + 1);
                j = pi[j];
            } else {
                j++;
            }
        }
    }

    return ret;
}

int main() {
    // Expected outcome : { 0, 9, 12 }
    // 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
    // A  A  B  A  A  C  A  A  D  A  A  B  A  A  B  A
    // A  A  B  A
    //                            A  A  B  A
    //                                     A  A  B  A
    string origin = "AABAACAADAABAABA", target = "AABA";
    vi ans = kmp(origin, target);

    for (auto idx : ans) {
        cout << idx << " ";
    }
    cout << "\n";

    return 0;
}
