#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Kruskal

// 并：合并
// 查：查找
// 集：集合

class UFSet {
public:
    void Init(int maxId);
    int Find(int id);
    bool Union(int id1, int id2);
    int Size() const;
private:
    unordered_map<int, int> m_far;  // m_far[x]  代表在这棵树上 x 的父结点编号
};

void UFSet::Init(int maxId) {
    m_far.clear();
    for (int i = 1; i <= maxId; ++i) {
        m_far[i] = i;
    }
}

int UFSet::Find(int id) {
    if (m_far[id] == id) {
        return id;
    }
    return m_far[id] = Find(m_far[id]);
}

bool UFSet::Union(int id1, int id2) {
    int s1 = Find(id1), s2 = Find(id2);
    if (s1 == s2) {
        return false;   // 合并失败
    }
    m_far[s1] = s2;
    return true;    // 合并成功
}

int UFSet::Size() const {
    return m_far.size();
}

template<typename T>
struct Edge {
    int u, v;
    T w;
};

template<typename T>
class Kruskal {
public:
    void Init(int maxId);
    void AddEdge(int u, int v, T w);
    T Solve();
private:
    UFSet m_ufs;
    vector< Edge<T> > m_edges;
};

template<typename T>
void Kruskal<T>::Init(int maxId) {
    m_ufs.Init(maxId);
    m_edges.clear();
}

template<typename T>
void Kruskal<T>::AddEdge(int u, int v, T w) {
    m_edges.push_back({ u, v, w });
}

template<typename T>
bool cmp(const Edge<T>& a, const Edge<T>& b) {
    return a.w < b.w;
}


template<typename T>
T Kruskal<T>::Solve() {
    T sum = 0;
    int edgeCount = 0;
    sort(m_edges.begin(), m_edges.end(), cmp<T>);
    for (int i = 0; i < m_edges.size(); ++i) {
        Edge<T>& e = m_edges[i];
        if (m_ufs.Union(e.u, e.v)) {
            sum += e.w;
            ++edgeCount;
        }
    }
    if (edgeCount < m_ufs.Size() - 1) {
        return -1;
    }
    return sum;
}

int main() {
    int n, m;
    Kruskal<long long> ks;
    cin >> n >> m;
    ks.Init(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        ks.AddEdge(a, b, c);
    }
    cout << ks.Solve() << endl;
    return 0;
}


