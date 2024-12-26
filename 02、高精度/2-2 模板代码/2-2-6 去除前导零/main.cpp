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

    void removeLeadingZeros();
public:
    BigInt();
    BigInt(const BigInt& bi);
    BigInt(char s[]);
    BigInt(int v);
    BigInt& operator=(const BigInt& bi);
    void print(char end);
    int compare(const BigInt& bi);

    BigInt operator+(const BigInt& bi) const;
    BigInt operator-(const BigInt& bi) const;
    BigInt operator*(const BigInt& bi) const;
    BigInt operator/(const BigInt& bi) const;
};

void BigInt::removeLeadingZeros() {
    while (m_size > 0 && m_data[m_size - 1] == 0) {
        m_size--;
    }
}


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
        m_data[m_size] += (s[i] - '0') * b;
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
    removeLeadingZeros();
}

// 1234567
//  0   1   2  ...
// 567 234 001 ...
BigInt::BigInt(int v) : m_size(0) {
    while (v > 0) {
        m_data[m_size++] = v % Base;
        v /= Base;
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

int BigInt::compare(const BigInt& bi) {
    if (m_size != bi.m_size) {
        return m_size > bi.m_size ? 1 : -1;
    }
    for (int i = m_size - 1; i >= 0; --i) {
        if (m_data[i] != bi.m_data[i]) {
            return m_data[i] > bi.m_data[i] ? 1 : -1;
        }
    }
    return 0;
}

BigInt BigInt::operator+(const BigInt& bi) const {
    BigInt ret;
    int i, carry = 0;
    // m_data[0]    = 501    m_size = 1
    // bi.m_data[0] = 499    bi.m_size = 1
    for (i = 0; i < m_size || i < bi.m_size || carry > 0; i++) {
        if (i < m_size) carry += m_data[i];
        if (i < bi.m_size) carry += bi.m_data[i];
        // 0 - Base-1
        ret.m_data[i] = carry % Base;  // carry = 1024
        carry /= Base;
    }
    ret.m_size = i;  // 0 - m_size-1 

    return ret;
}

// 1000000 - 999001 = ?
//  0   1   2
// 000 000 001
// 001 999 000
// 999 000 000  m_size = 1
BigInt BigInt::operator-(const BigInt& bi) const {
    BigInt ret;
    int carry = 0;
    ret.m_size = m_size;
    for (int i = 0; i < ret.m_size; ++i) {
        ret.m_data[i] = m_data[i] - carry;
        if (i < bi.m_size) {
            ret.m_data[i] -= bi.m_data[i];
        }
        if (ret.m_data[i] < 0) {
            carry = 1;
            ret.m_data[i] += Base;
        }
        else {
            carry = 0;
        }
    }
    ret.removeLeadingZeros();
    return ret;
}

BigInt BigInt::operator*(const BigInt& bi) const {
    BigInt ret;
    ret.m_size = m_size + bi.m_size;
    for (int i = 0; i < ret.m_size; ++i) {
        ret.m_data[i] = 0;
    }
    for (int i = 0; i < m_size; ++i) {
        int carry = 0;
        for (int j = 0; j < bi.m_size; ++j) {
            ret.m_data[i + j] += m_data[i] * bi.m_data[j] + carry;
            if (ret.m_data[i + j] >= Base) {
                carry = ret.m_data[i + j] / Base;
                ret.m_data[i + j] %= Base;
            }
            else {
                carry = 0;
            }
        }
        ret.m_data[i + bi.m_size] += carry;
    }
    ret.removeLeadingZeros();
    return ret;
}

// 1、计算的是整数之间的相除
// 2、不考虑符号位
// 3、得到的结果是去下整后的结果
/*
    0822
    ----
12 /9875
    9
    0
    ----
    98
    96
    ----
     27
     24
     ---
      35
      24
      --
      11

12x <= c 最大的 x
二分枚举 - 二分查找
*/
BigInt BigInt::operator/(const BigInt& bi) const {
    BigInt ret, carry = 0;
    int left, right, mid;
    for (int i = m_size - 1; i >= 0; --i) {
        carry = carry * Base + m_data[i];
        left = -1;
        right = Base;
        while (left + 1 < right) {
            mid = (left + right) / 2;
            if ((bi * mid).compare(carry) <= 0) {
                // 12 * x <= c
                left = mid;
            }
            else {
                right = mid;
            }
        }
        ret.m_data[i] = left;
        carry = carry - bi * left;
    }
    ret.m_size = m_size;
    ret.removeLeadingZeros();
    return ret;
}

int main() {
    char s1[100], s2[100];
    while (cin >> s1 >> s2) {
        BigInt a(s1), b(s2);
        (a + b).print('\n');
        (a - b).print('\n');
        (a * b).print('\n');
        (a / b).print('\n');
    }
    return 0;
}