#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;

vi mobius(int n) {
    vi p(n + 1), m(n + 1);

    for (int i = 2; i <= n; i++) { p[i] = 1; }
    for (int i = 1; i <= n; i++) { m[i] = 1; }
    for (int i = 2; i <= n; i++) {
        if (p[i]) {
            for (int j = 1; j <= n / i; j++) {
                if (j >= i) { p[i * j] = 0; }
                m[i * j] *= (-1);
                if (j % i == 0) { m[i * j] = 0; }
            }
        }
    }

    return m;
}

int main() {
    vi m = mobius(30);
    for (int i = 1; i <= 30; i++) {
        cout << "mobius(" << i << ") = " << m[i] << "\n";
    }
}