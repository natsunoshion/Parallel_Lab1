#include <iostream>

using namespace std;

int a[10240], sum;

void recursion(int n) {
    int m;
    for (m=n; m>1; m/=2) {
        for (int i=0; i < m/2; i++) {
            a[i] = a[i*2] + a[i*2 + 1];
        }
    }  // a[0]为最终结果
    sum = a[0];
}

int main() {
    for (int i=0; i<10000; i++) {
        sum = 0;
        int n = 8192;
        for (int i=0; i<n; i++) {
            a[i] = i;
        }
        recursion(n);
    }
    cout << sum;
    return 0;
}