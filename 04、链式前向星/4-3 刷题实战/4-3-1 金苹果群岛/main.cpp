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

    int m_count;
    vector<int> m_colors;         // m_colors[i] 代表的是每个岛屿被染色后的颜色值，一开始没被染色的时候是-1

    void dfs(int u);             // 从 u 出发，把所有和 u 直接或者间接相连的岛屿进行染色
public:
    Graph(int n);
    void addEdge(int from, int to, T weight);
    void printEdges();
    int countConnectedBlock();  // 利用这个函数，来统计一张图中，连通分量的个数
};

template<class T>
void Graph<T>::dfs(int u) {
    if (m_colors[u] != -1) {
        return;
    }
    m_colors[u] = m_count;
    for (int e = m_head[u]; e != -1; e = m_edges[e].next) {
        dfs(m_edges[e].to);
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
int Graph<T>::countConnectedBlock() {
    int n = (int)m_head.size();
    m_count = 0;
    m_colors.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        if (m_colors[i] == -1) {
            dfs(i);
            m_count++;
        }
    }
    return m_count;
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph <int> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.addEdge(a, b, 0);
        g.addEdge(b, a, 0);
    }
    cout << g.countConnectedBlock() - 1 << endl;

    return 0;
}

