#include <iostream>
#include <stack>
using namespace std;

/* 单调栈模板 */
#define maxn 300001
#define inf -1

template<typename T>
bool cmp(T a, T b) {
    return a < b;
}

// ans[i] 代表从 i 往左找，找到的第一个 满足条件 的下标
template<typename T>
void findFirstMeetOnLeft(int n, T h[], int ans[]) {
    stack<int> stk;
    h[0] = inf;
    stk.push(0);
    for (int i = 1; i <= n; ++i) {
        while (!cmp(h[stk.top()], h[i])) {
            stk.pop();
        }
        ans[i] = stk.top();
        stk.push(i);
    }
}

template<typename T>
void reverseArray(int n, T arr[]) {
    for (int i = 1; i <= n / 2; ++i) {
        T tmp = arr[i];
        arr[i] = arr[n + 1 - i];
        arr[n + 1 - i] = tmp;
    }
}

/* 单调栈模板 */

int h[maxn], l[maxn], r[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }
    findFirstMeetOnLeft(n, h, l);
    reverseArray(n, h);
    findFirstMeetOnLeft(n, h, r);
    reverseArray(n, h);
    reverseArray(n, r);
    for (int i = 1; i <= n; ++i) {
        r[i] = (n+1) - r[i];
    }
    long long max = 0;
    for (int i = 1; i <= n; ++i) {
        // r[i] - 1; 就是值 >= h[i] 的最大下标
        // l[i] + 1; 就是值 >= h[i] 的最小下标
        long long x = (r[i] - 1) - (l[i] + 1) + 1;
        x = x * h[i];
        if (x > max) {
            max = x;
        }
    }
    cout << max << endl;

    return 0;
}

