#include <iostream>
#include <cstring>    // #include <string.h>
using namespace std;

// 当 Base=10 的时候，取值范围就是 [0,9]
// 当 Base=1000 的时候，取值范围就是 [0, 999]
const int Base = 1000;
const int Capacity = 100;

// 1234567
//  0   1   2   3  ...
// 567 234 001 000 ...

class BigInt {
private:
    int m_data[Capacity];
    int m_size;
public:
    BigInt();
    BigInt(const BigInt& bi);
    BigInt(char s[]);
    BigInt& operator=(const BigInt& bi);
    void print(char end);
};

BigInt::BigInt() : m_size(0) {
    memset(m_data, 0, sizeof(m_data));
}

BigInt::BigInt(const BigInt& bi) : m_size(bi.m_size) {
    memcpy(m_data, bi.m_data, sizeof(bi.m_data));
}

// 1234567
// m_data[] = {567, 234, 001};
// m_size = 3;
BigInt::BigInt(char s[]) {
    int b = 1;
    m_size = 0;
    m_data[m_size] = 0;
    for (int i = strlen(s) - 1; i >= 0; --i) {
        m_data[m_size] += (s[i] - '0')* b;
        b *= 10;
        if (b >= Base) {
            b = 1;
            m_size++;
            m_data[m_size] = 0;
        }
    }
    if (m_data[m_size] > 0) {   // [0, m_size-1]
        m_size++;
    }
}

BigInt& BigInt::operator=(const BigInt& bi) {
    m_size = bi.m_size;
    memcpy(m_data, bi.m_data, sizeof(m_data));
    return *this;
}

void BigInt::print(char end) {
    cout << (m_size == 0 ? 0 : m_data[m_size - 1]);
    for (int i = m_size - 2; i >= 0; --i) {
        for (int j = Base / 10; j > 0; j /= 10) {
            // 100 10 1
            // m_data[i] = 567
            // 567/100%10 = 5
            // 567/10%10  = 6
            // 567/1%10   = 7
            cout << (m_data[i] / j) % 10;
        }
    }
    cout << end;
}

int main() {
    char s[1000];
    while (cin >> s) {
        BigInt b(s);
        b.print('\n');
    }
    return 0;
}