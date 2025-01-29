#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class SegmentTree {
private:
    // m_tree[node] 代表 node 这个结点管辖的区间的元素和
    vector<T> m_tree;
    // m_lazy[node] 就代表 node 这个结点的懒标记
    vector<T> m_lazy;
    int m_size;

    void build(const vector<T>& arr, int node, int start, int end);
    void pushDown(int node, int start, int end);
    void updateRange(int node, int start, int end, int l, int r, T val);
    T queryRange(int node, int start, int end, int l, int r);

public:
    SegmentTree(const vector<T>& arr);
    // 代表在 [l, r] 这个区间中，每个元素都累加上一个 val
    void Update(int l, int r, T val);
    // 代表返回 [l, r] 这个区间中元素的和
    T Query(int l, int r);
};

template<typename T>
void SegmentTree<T>::build(const vector<T>& arr, int node, int start, int end) {
    if (start == end) {
        m_tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    build(arr, leftChild, start, mid);
    build(arr, rightChild, mid + 1, end);

    m_tree[node] = m_tree[leftChild] + m_tree[rightChild];
}

template<typename T>
void SegmentTree<T>::pushDown(int node, int start, int end) {
    if (m_lazy[node] != 0) {
        int mid = (start + end) / 2;
        int leftChild = node * 2 + 1;
        int rightChild = node * 2 + 2;
        m_tree[leftChild] += m_lazy[node] * (mid - start + 1);
        m_tree[rightChild] += m_lazy[node] * (end - mid);
        m_lazy[leftChild] += m_lazy[node];
        m_lazy[rightChild] += m_lazy[node];
        m_lazy[node] = 0;
    }
}

template<typename T>
void SegmentTree<T>::updateRange(int node, int start, int end, int l, int r, T val) {
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        m_tree[node] += val * (end - start + 1);
        m_lazy[node] += val;
        return;
    }
    pushDown(node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    updateRange(leftChild, start, mid, l, r, val);
    updateRange(rightChild, mid + 1, end, l, r, val);
    m_tree[node] = m_tree[leftChild] + m_tree[rightChild];
}

template<typename T>
T SegmentTree<T>::queryRange(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return 0;
    if (start >= l && end <= r) {
        return m_tree[node];
    }
    pushDown(node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    T leftSum = queryRange(leftChild, start, mid, l, r);
    T rightSum = queryRange(rightChild, mid + 1, end, l, r);
    return leftSum + rightSum;
}

template<typename T>
SegmentTree<T>::SegmentTree(const vector<T>& arr) {
    m_size = (int)arr.size();
    m_tree.resize(4 * m_size);
    m_lazy.resize(4 * m_size, 0);
    build(arr, 0, 0, m_size - 1);
}

template<typename T>
void SegmentTree<T>::Update(int l, int r, T val) {
    updateRange(0, 0, m_size - 1, l, r, val);
}

template<typename T>
T SegmentTree<T>::Query(int l, int r) {
    return queryRange(0, 0, m_size - 1, l, r);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    SegmentTree<long long> stree(arr);
    while (m--) {
        int z, x, y, k;
        cin >> z;
        if (z == 1) {
            cin >> x >> y >> k;
            x -= 1;
            y -= 1;
            stree.Update(x, y, k);
        }
        else {
            cin >> x >> y;
            x -= 1;
            y -= 1;
            cout << stree.Query(x, y) << endl;
        }
    }
    return 0;
}


