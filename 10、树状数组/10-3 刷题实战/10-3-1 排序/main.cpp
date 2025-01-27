#include <iostream>
#include <vector>
using namespace std;


template<class T>
class FenwickTree {
private:
    vector<T> m_tree;
    int lowbit(int x);  // 12 -> 1100 lowbit -> 100
public:
    FenwickTree(int n) : m_tree(n + 1, 0) {}
    void Update(int idx, T val);
    T Query(int idx);
    T Query(int l, int r);
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

int a[1000001];

int main() {
    int n;
    cin >> n;
    FenwickTree<long long> ft(1000000);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        ft.Update(a[i], 1);
        sum += (long long)a[i] * ft.Query(a[i] - 1);
    }
    cout << sum << endl;
    return 0;
}