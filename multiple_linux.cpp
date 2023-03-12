#include <iostream>
#include <sys/time.h>
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
    int step = 100;
    long counter;
    float us;
    struct timeval start, end;  // 计时
    for (int n=0; n<=10000; n+=step) {  // 规模递增
        init(n);
        counter = 0;
        // 计时开始
        gettimeofday(&start, NULL);
        while (counter < 10) {  // 重复实验提高精度
            counter++;
            for (int i=0; i<n; i++) {
                sum[i] = 0.0;
                for (int j=0; j<n; j++)
                    sum[i] += b[j][i] * a[i];
            }
        }
        gettimeofday(&end, NULL);
        // 计时结束
        us = (end.tv_sec-start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;  // 微秒
        cout << "规模" << n << ':';
        cout << "平凡算法" << ' ' << us / counter / 1000 << ' ';

        counter = 0;
        gettimeofday(&start, NULL);
        
        while (counter < 10) {
            counter++;
            for (int i=0; i<n; i++) {
                sum[i] = 0;
            }
            for (int j=0; j<n; j++) {
                for (int i=0; i<n; i++)
                    sum[i] += b[j][i] * a[i];
            }
        }
        gettimeofday(&end, NULL);
        us = (end.tv_sec-start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        cout << "Cache优化算法" << ' ' << us / counter / 1000 << endl;
        if (n == 1000) step = 1000;
    }
}