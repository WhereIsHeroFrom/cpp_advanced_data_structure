#include <iostream>
using namespace std;

// priority_queue

/*
      0
    /   \
   1     2
 /  \   / \ 
3    4 5   6
*/

#define maxn 100010
#define lson(idx) (2*idx+1)
#define rson(idx) (2*idx+2)
#define parent(idx) ((idx-1)/2)

template<typename T>
struct Small {
    bool operator()(const T& left, const T& right) const {
        return left < right;
    }
};

template<typename T>
struct Big {
    bool operator()(const T& left, const T& right) const {
        return left > right;
    }
};

template<class T, typename cmp>
class Heap {
private:
    void shiftUp(int curr);
    void shiftDown(int curr);

public:
    Heap(int cap = maxn);
    ~Heap();
    void push(const T& data);
    void pop();
    T top() const;
    bool empty() const;
    void clear();
private:
    T* m_data;
    int m_size;
    int m_capacity;
    cmp m_cmp;
};

template<class T, typename cmp>
void Heap<T, cmp>::shiftUp(int curr) {
    if (curr == 0) {
        return;
    }
    int par = parent(curr);
    if (m_cmp(m_data[curr], m_data[par])) {
        swap(m_data[curr], m_data[par]);
        shiftUp(par);
    }
}

/*
    curr
      \ 
      optId
*/
template<class T, typename cmp>
void Heap<T, cmp>::shiftDown(int curr) {
    int lsonId = lson(curr);
    int rsonId = rson(curr);
    int optId = curr;
    if (lsonId < m_size && m_cmp(m_data[lsonId], m_data[optId])) {
        optId = lsonId;
    }
    if (rsonId < m_size && m_cmp(m_data[rsonId], m_data[optId])) {
        optId = rsonId;
    }
    if (optId != curr) {
        swap(m_data[curr], m_data[optId]);
        shiftDown(optId);
    }
}

template<class T, typename cmp>
Heap<T, cmp>::Heap(int cap) {
    m_data = new T[cap];
    m_capacity = cap;
    m_size = 0;
}

template<class T, typename cmp>
Heap<T, cmp>::~Heap() {
    delete[] m_data;
    m_data = NULL;
}

template<class T, typename cmp>
void Heap<T, cmp>::push(const T& data) {
    m_data[m_size++] = data;
    shiftUp(m_size - 1);
}

template<class T, typename cmp>
void Heap<T, cmp>::pop() {
    swap(m_data[0], m_data[m_size - 1]);
    --m_size;
    shiftDown(0);
}

template<class T, typename cmp>
T Heap<T, cmp>::top() const {
    return m_data[0];
}

template<class T, typename cmp>
bool Heap<T, cmp>::empty() const {
    return m_size == 0;
}

template<class T, typename cmp>
void Heap<T, cmp>::clear() {
    m_size = 0;
}

int main() {
    Heap<int, Big<int> > q;
    for (int i = 0; i < 5; ++i) {
        int x = rand() % 30, y = rand() % 30;
        q.push(x);
        q.push(y);
        cout << "塞入两个数：" << x << ' ' << y << endl;
        cout << "目前最大的数是：" << q.top() << endl;
        q.pop();
        cout << "弹出最大的那个数" << endl;
    }
    return 0;
}

