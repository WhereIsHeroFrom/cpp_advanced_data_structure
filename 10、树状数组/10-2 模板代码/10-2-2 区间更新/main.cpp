#include <iostream>
#include <vector>
using namespace std;

// 模板2：区间更新，单点求值
// https://www.luogu.com.cn/problem/P3368
template<class T>
class FenwickTree {
private:
    vector<T> m_tree;
    int lowbit(int x);  // 12 -> 1100 lowbit -> 100
    void Update(int idx, T val);
    T Query(int idx);
    T Query(int l, int r);
public:
    FenwickTree(int n) : m_tree(n + 2, 0) {}
    void UpdateInterval(int l, int r, T val);
    T QueryIndex(int idx);
};

// 10101000 对于这个数字，lowbit(10101000) 得到的结果就是 1000 ，也就是十进制的 8
// 对于一个 8 位整数
// x = 00101000
//-x = 11011000
// 0 =100000000 
// x & -x = 1000
template<class T>
int FenwickTree<T>::lowbit(int x) {
    return x & (-x);
}

template<class T>
void FenwickTree<T>::Update(int idx, T val) {
    int n = (int)m_tree.size();
    while (idx < n) {
        m_tree[idx] += val;
        idx += lowbit(idx);
    }
}

template<class T>
T FenwickTree<T>::Query(int idx) {
    T sum = 0;
    while (idx > 0) {
        sum += m_tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}

template<class T>
T FenwickTree<T>::Query(int l, int r) {
    return Query(r) - Query(l - 1);
}

template<class T>
void FenwickTree<T>::UpdateInterval(int l, int r, T val) {
    Update(l, val);
    Update(r + 1, -val);
}

template<class T>
T FenwickTree<T>::QueryIndex(int idx) {
    return Query(idx);
}

int main() {
    int n, m;
    cin >> n >> m;
    FenwickTree<int> ft(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        ft.UpdateInterval(i, i, x);
    }
    while (m--) {
        int z, x, y, k;
        cin >> z;
        if (z == 1) {
            cin >> x >> y >> k;
            ft.UpdateInterval(x, y, k);
        }
        else {
            cin >> x;
            cout << ft.QueryIndex(x) << endl;
        }
    }
    return 0;
}

