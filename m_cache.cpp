#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int N = 10240;  // 最大规模

double b[N][N] , sum[N], a[N];

void init(int n) {  // 初始化
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            b[i][j] = i + j;
    for (int i=0; i<n; i++) {
        a[i] = i;
    }
}

int main() {
    init(N);
    for (int i=0; i<N; i++) {
        sum[i] = 0;
    }
    for (int j=0; j<N; j++) {
        for (int i=0; i<N; i++)
            sum[i] += b[j][i] * a[i];
    }
    return 0;
}