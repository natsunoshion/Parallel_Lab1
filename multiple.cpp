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
    int step = 100;
    long counter;
    float ms;
    long long head, tail, freq;  // 计时
    for (int n=0; n<=10000; n+=step) {  // 规模递增
        init(n);
        counter = 0;
        // 计时开始
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        
        while (counter < 10) {  // 重复实验提高精度
            counter++;
            for (int i=0; i<n; i++) {
                sum[i] = 0.0;
                for (int j=0; j<n; j++)
                    sum[i] += b[j][i] * a[i];
            }
        }
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        // 计时结束
        ms = (tail-head) * 1000 / freq;
        cout << "规模" << n << ':';
        cout << "平凡算法" << ' ' << ms / counter << ' ';

        counter = 0;
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        
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
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        ms = (tail-head) * 1000 / freq;
        cout << "Cache优化算法" << ' ' << ms / counter << endl;
        if (n == 1000) step = 1000;
    }
}