#include<iostream>
#include<vector>
#include<algorithm>
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

#define maxn 100001
struct HB {
    int h, b;
}hb[maxn];
int k[maxn], maxv[maxn];

bool cmp(const HB& a, const HB& b) {
    return a.h < b.h;
}

int main() {
    Dicretizer<int> d;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> hb[i].h;
        d.AddData(hb[i].h);
    }
    for (int i = 0; i < n; ++i) {
        cin >> hb[i].b;
    }
    for (int i = 0; i < q; ++i) {
        cin >> k[i];
        d.AddData(k[i]);
    }
    d.Process();
    for (int i = 0; i < n; ++i) {
        hb[i].h = d.Get(hb[i].h);
    }
    for (int i = 0; i < q; ++i) {
        k[i] = d.Get(k[i]);
    }
    sort(hb, hb + n, cmp);
    maxv[d.Size()] = -1;
    int j = n - 1;
    for (int i = d.Size() - 1; i >= 0; --i) {
        maxv[i] = maxv[i + 1];  // i 对应的高度，不一定是山的高度，也可能是那个询问 k
        while (j >= 0 && hb[j].h == i) {
            if (hb[j].b > maxv[i]) {
                maxv[i] = hb[j].b;
            }
            --j;
        }
    }
    for (int i = 0; i < q; ++i) {
        int x = k[i];
        cout << maxv[x] << endl;
    }


    return 0;
}

