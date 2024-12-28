#include <iostream>
#include <vector>
using namespace std;

/* C++链式前向星模板 */

// 边的起点是不需要存储的
// 因为所有起点相同的边，会被一个链表链接起来
template<typename T>
struct Edge {
    int to;
    T weight;
    int next;
};

template<class T>
class Graph {
private:
    vector< Edge<T> > m_edges;   // m_edges[i] 代表的就是编号为 i 的这条边
    vector<int> m_head;          // m_head[i] 表示的是以i作为起点的那个链表的链表头

    vector<bool>    m_visited;   // m_visited[i] 为 true 的时候，代表访问过了；否则代表没有被访问
    void dfs(int u, int& ans);   // u代表从当前点开始访问，ans代表访问过程中编号的最大值
public:
    Graph(int n);
    void addEdge(int from, int to, T weight);
    void printEdges();
    int caculateColor(int u);    // 代表从 u 出发，能够访问到的最大结点的编号
};

template<class T>
void Graph<T>::dfs(int u, int& ans) {
    if (m_visited[u]) {
        return;
    }
    m_visited[u] = true;
    if (u > ans) {
        ans = u;
    }
    for (int e = m_head[u]; e != -1; e = m_edges[e].next) {
        // (u -> v)
        int v = m_edges[e].to;
        dfs(v, ans);
    }
}

template<class T>
Graph<T>::Graph(int n) {
    m_edges.clear();
    m_head.resize(n, -1);   // m_head 是一个值都为-1的数组
}

template<class T>
void Graph<T>::addEdge(int from, int to, T weight) {
    m_edges.push_back(Edge<T>{to, weight, m_head[from]});
    m_head[from] = (int)m_edges.size() - 1;
}

template<class T>
void Graph<T>::printEdges() {
    int n = m_head.size();
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int e = m_head[i]; e != -1; e = m_edges[e].next) {
            int v = m_edges[e].to;
            T w = m_edges[e].weight;
            cout << "(" << v << "," << w << ")";
        }
        cout << endl;
    }
}

/* C++链式前向星模板 */

template<class T>
int Graph<T>::caculateColor(int u) {
    int n = m_head.size();
    m_visited.resize(n);
    for (int i = 0; i < n; ++i) {
        m_visited[i] = false;
    }
    int ans = u;
    dfs(u, ans);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph<int> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.addEdge(a, b, 0);
    }
    for (int i = 0; i < n; ++i) {
        cout << g.caculateColor(i) + 1 << " ";
    }
    cout << endl;
    return 0;
}

