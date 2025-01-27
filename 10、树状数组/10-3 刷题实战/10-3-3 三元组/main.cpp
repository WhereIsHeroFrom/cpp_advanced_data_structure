#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1 1.5 -5 20 -5 10000000000
// 第一步：排序  -5 -5 1 1.5 20 10000000000
// 第二步：去重  -5 1 1.5 20 10000000000
//               0  1 2   3  4

template<class T>
class Dicretizer {
public:
    void AddData(T v);
    void Process();
    int Get(T v) const;
    int Size() const;
private:
    vector<T> m_data;
};

template<class T>
void Dicretizer<T>::AddData(T v) {
    m_data.push_back(v);
}

template<class T>
void Dicretizer<T>::Process() {
    sort(m_data.begin(), m_data.end());
    int lastIdx = 0;
    for (int i = 1; i < m_data.size(); ++i) {
        T x = m_data[i];
        if (x != m_data[lastIdx]) {
            m_data[++lastIdx] = x;
        }
    }
    // 0,1,2,3,4...lastIdx,    lastIdx+1 ... m_data.size()-1
    while (lastIdx + 1 < m_data.size()) {
        m_data.pop_back();
    }
}

template<class T>
int Dicretizer<T>::Get(T v) const {
    int l = -1, r = (int)m_data.size();
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (m_data[mid] >= v) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    // l 就是最大的 < v 的下标
    // r 就是最小的 >= v 的下标
    if (r == m_data.size() || m_data[r] != v) {
        return -1;
    }
    return r;
}

template<class T>
int Dicretizer<T>::Size() const {
    return m_data.size();
}


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

#define mod 998244353
#define maxn 200001

int a[maxn];
int lt[maxn];  // lt[i] 表示小于 a[i] 的数的个数

int main() {
    int n;
    cin >> n;
    Dicretizer<int> d;
    FenwickTree<int> ft(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        d.AddData(a[i]);
    }
    d.Process();
    for (int i = 0; i < n; ++i) {
        a[i] = d.Get(a[i]) + 1;
    }
    for (int i = 0; i < n; ++i) {
        ft.Update(a[i], 1);
        lt[i] = ft.Query(a[i] - 1);
    }
    ft = FenwickTree<int>(n);
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        ft.Update(a[i], 1);
        int gt = ft.Query(a[i] + 1, n);
        sum += (long long)lt[i] * gt % mod;
        sum %= mod;
    }
    cout << sum << endl;
    return 0;
}