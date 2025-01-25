#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 离散化模板
// https://www.luogu.com.cn/problem/B3694

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

int a[100001];

int main() {
    int t;
    while (cin >> t) {
        while (t--) {
            Dicretizer<int> d;
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
                d.AddData(a[i]);
            }
            d.Process();
            for (int i = 0; i < n; ++i) {
                cout << d.Get(a[i]) + 1 << ' ';
            }
            cout << endl;
        }
    }
        
    return 0;
}

