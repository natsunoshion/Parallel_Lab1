#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int a[10240], sum;

// 初始化
void init(int n) {
    for (int i=0; i<n; i++) {
        a[i] = i;
    }
}

// 平凡算法
void common(int n) {
    // #pragma UNROLL(4)
    for (int i=0; i<n; i++) {
        sum += a[i];
    }
}

// 多路链式
void multi(int n) {
    int sum1 = 0, sum2 = 0;
    for (int i=0; i<n; i+=2) {
        sum1 += a[i];
        sum2 += a[i+1];  // n必须是偶数
    }
    sum = sum1 + sum2;
}

void multi_3(int n) {
    int sum1 = 0, sum2 = 0, sum3 = 0;
    for (int i=0; i<n; i+=3) {
        sum1 += a[i+1];
        sum2 += a[i+2];  // n必须是3的倍数
        sum3 += a[i+3];
    }
    sum = sum1 + sum2 + sum3;
}

// 递归函数
void recursion(int n) {
    if (n == 1) {
        return;
    } else {
        for (int i=0; i < n/2; i++) {
            a[i] += a[n-i-1];
        }
        n /= 2;
        recursion(n);
    }
    sum = a[0];
    return;
}

int main() {
    long long head, tail, freq;
    float ms;
    int n = 216;  // 规模
    while (n < 2000) {
        // 计时开始
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        int counter = 0;
        while (counter < 10000) {  // 重复10000次，增大时间
            init(n);
            sum = 0;
            counter++;
            common(n);
        }
        // 计时结束
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        ms = (tail-head) * 1000 / freq;
        cout <<  "规模" << n << ':';
        cout << "平凡算法" << ' ' << ms / counter << ' ';

        // 计时开始
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        counter = 0;
        while (counter < 10000) {
            init(n);
            sum = 0;
            counter++;
            multi(n);
        }
        // 计时结束
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        ms = (tail-head) * 1000 / freq;
        cout << "二路优化算法" << ' ' << ms / counter << ' ';

        // 计时开始
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        counter = 0;
        while (counter < 10000) {
            init(n);
            sum = 0;
            counter++;
            multi_3(n);
        }
        // 计时结束
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        ms = (tail-head) * 1000 / freq;
        cout << "三路优化算法" << ' ' << ms / counter << endl;

        // 计时开始
        QueryPerformanceFrequency((LARGE_INTEGER *)& freq);
        QueryPerformanceCounter((LARGE_INTEGER *)& head);
        counter = 0;
        while (counter < 10000) {
            init(n);
            sum = 0;
            counter++;
            recursion(n);
        }
        // 计时结束
        QueryPerformanceCounter((LARGE_INTEGER *)& tail);
        ms = (tail-head) * 1000 / freq;
        cout << "递归优化算法" << ' ' << ms / counter << endl;

        n += 216;
    }
}