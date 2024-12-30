#include <iostream>
#include <stack>
using namespace std;

/* 单调栈模板 */
#define maxn 700001
#define inf 2000000000

template<typename T>
bool cmp(T a, T b) {
    return a > b;
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

int h[maxn], ans[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }
    findFirstMeetOnLeft(n, h, ans);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) ans[i] = -1;
        cout << ans[i] << ' ';
    }
    cout << endl;
    reverseArray(n, h);
    findFirstMeetOnLeft(n, h, ans);
    reverseArray(n, ans);
    reverseArray(n, h);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) ans[i] = -1;
        else ans[i] = (n + 1) - ans[i];
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
