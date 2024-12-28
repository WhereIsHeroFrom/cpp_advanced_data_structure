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

public:
    Graph(int n);
    void addEdge(int from, int to, T weight);
    void printEdges();
};

template<class T>
Graph<T>::Graph(int n) {
    m_edges.clear();
    m_head.resize(n, -1);   // m_head 是一个值都为-1的数组
}

template<class T>
void Graph<T>::addEdge(int from, int to, T weight) {
    m_edges.push_back( Edge<T>{to, weight, m_head[from]} );
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

int main() {
    int n, m;
    cin >> n >> m;
    Graph<int> g(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g.addEdge(a, b, c);
    }
    g.printEdges();
    return 0;
}

