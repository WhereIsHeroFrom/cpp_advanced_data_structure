#include <iostream>
#include <deque>
using namespace std;

/* 单调队列模板 */
#define maxn 100001

template<typename T>
bool max(T a, T b) {
    return a <= b;
}

template<typename T>
bool min(T a, T b) {
    return a >= b;
}

// 给定一个长度为 n 的序列 
// 并且一个区间长度 k
// 求出所有长度不超过 k 的连续区间中的 最大值（最小值）
template <typename T>
void findIntervalMinMax(int n, T h[], int k, T ans[], bool (*cmp)(T a, T b)) {
    // ans[i] 代表的就是以 i 结尾的 且最大长度为 k 的区间里面的最大值（最小值）
    deque<int> q;
    for (int i = 0; i < n; ++i) {
        while ( !q.empty() && cmp( h[ q.back() ], h[i] )) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.back() - q.front() + 1 > k) {
            q.pop_front();
        }
        // ans[i] 表示以 i 结尾，且长度不超过 k 的区间中，元素的最大值（最下值）
        ans[i] = h[ q.front() ];
    }
}
/* 单调队列模板 */


int main() {
    int h[] = { 8,7,6,9,11 };
    int ans[10];
    findIntervalMinMax(5, h, 3, ans, max);
    for (int i = 0; i < 5; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    findIntervalMinMax(5, h, 3, ans, min);
    for (int i = 0; i < 5; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}