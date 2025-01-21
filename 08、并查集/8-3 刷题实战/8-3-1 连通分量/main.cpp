#include <iostream>
#include <unordered_map>
using namespace std;

// P3367 【模板】并查集
// https://www.luogu.com.cn/problem/P3367

// 并：合并
// 查：查找
// 集：集合

class UFSet {
public:
    void Init(int maxId);
    int Find(int id);
    bool Union(int id1, int id2);
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

int main() {
    int n, m;
    UFSet ufs;
    cin >> n >> m;
    int count = n;
    ufs.Init(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (ufs.Union(a, b)) {
            count--;
        }
    }
    cout << count << endl;
    return 0;
}


