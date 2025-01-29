#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<typename T, typename Compare>
class SparseTable {
private:
    vector<T> m_org;
    vector< vector<int> > m_st;
    Compare m_cmp;
    void init();
public:
    SparseTable(const vector<T>& arr);
    int Query(int l, int r);
};

template<typename T, typename Compare>
void SparseTable<T, Compare>::init() {
    int n = (int)m_org.size();
    // log2(n)+1,  n
    int log2n = (int)log2(n) + 1;
    m_st.assign(log2n, vector<int>(n));
    // st[j][i] 表示的是 [i, i + 2^j-1 ] 这个区间中的最值（所在的下标）
    // st[0][i] 表示的是 [i, i] 这个区间中的最值（所在的下标），那就是 i
    for (int i = 0; i < n; ++i) {
        m_st[0][i] = i;
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            // [i, i+(1<<j)-1]
            /*
                1、st[j][i] 的区间长度是 2^j
                2、把它拆成两个长度为 2^(j-1) 的区间
                   2.1 一个区间是 [i, i + 2^(j-1) - 1]           =>  st[j-1][i]
                   2.2 一个区间是 [i + 2^(j-1), i + 2^j - 1]     =>  st[j-1][i + (1<<(j-1))]
            */
            int idx1 = m_st[j - 1][i];
            int idx2 = m_st[j - 1][i + (1 << (j - 1))];
            m_st[j][i] = m_cmp(m_org[idx1], m_org[idx2]) ? idx1 : idx2;
        }
    }

}

template<typename T, typename Compare>
SparseTable<T, Compare>::SparseTable(const vector<T>& arr) {
    int n = (int)arr.size();
    m_org.assign(arr.begin(), arr.end());
    init();
}

/*
1、对于 [l, r] 这个区间，可以拆分成两个长度分别为 2^k 的区间：
    一个区间是以 l 作为起始的： [l, x]
    一个区间是以 r 作为结尾的： [y, r]
    并且，这两个区间的并集是 [l, r]， 所以需要满足 x+1 >= y
2、以 l 作为起始的区间的长度为 2 的 k 次
        它表示的区间就是 [l, l + 2^k - 1]    => x = l + 2^k - 1
   以 r 作为结尾的区间的长度为 2 的 k 次
        它表示的区间就是 [r - 2^k + 1, r]    => y = r - 2^k + 1
3、l + 2^k - 1 + 1 >= r - 2^k + 1
    移项：     2^(k+1)  >= r - l + 1
    取对数：     k      >= log2(r - l + 1) - 1
    所以 k 的值，为 log2(r - l + 1) 取上整 再减一
*/
template<typename T, typename Compare>
int SparseTable<T, Compare>::Query(int l, int r) {
    if (l == r) {
        return l;
    }
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = m_st[k][l];
    int idx2 = m_st[k][r - (1 << k) + 1];
    return m_cmp(m_org[idx1], m_org[idx2]) ? idx1 : idx2;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch>'9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48; ch = getchar(); }
    return x * f;
}

int main() {
    int n, m;
    n = read();
    m = read();
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = read();
    }
    SparseTable<int, std::less<int> > stl(arr);
    SparseTable<int, std::greater<int> > stg(arr);
    long long minsum = 0, maxsum = 0;
    while (m--) {
        int l = read();
        int r = read();
        --l, --r;
        minsum += arr[stl.Query(l, r)];
        maxsum += arr[stg.Query(l, r)];
    }
    cout << minsum << ' ' << maxsum << endl;

    return 0;
}


