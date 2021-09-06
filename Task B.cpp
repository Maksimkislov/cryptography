#include <iostream>
#include <vector>
using namespace std;

typedef vector<unsigned long long> lnum;

long long Pow(unsigned long long x, unsigned long long n, unsigned long long p) {
    if (n == 0)
        return 1;
    if (n % 2 == 1) {
        return Pow(x, n - 1, p) * x % p;
    }
    else {
        unsigned long long a = Pow(x, n / 2, p);
        return (a * a) % p;
    }
}

unsigned long long char_to_number(char symbol) {
    if (symbol >= 48 && symbol <= 57)
        return symbol - 48;
    if (symbol >= 65 && symbol <= 90)
        return symbol - 55;
    if (symbol >= 97 && symbol <= 122)
        return symbol - 61;
    if (symbol == 32)
        return 62;
    if (symbol == 46)
        return 63;
    return 64;
}

char intToChar(unsigned long long code) {
    if (code >= 0 && code <= 9) {
        return code + '0';
    }
    else if (code >= 10 && code <= 35) {
        return code + 'A' - 10;
    }
    else if (code <= 61) {
        return code + '=';
    }
    else if (code == 62) {
        return ' ';
    }
    else {
        return '.';
    }
}


void sumLongNmbrs(lnum& a, const lnum& b, unsigned long long base) {
    unsigned long long carry = 0;
    for (unsigned long long i = 0; i < max((unsigned long long)a.size(), (unsigned long long)b.size()) || carry; ++i) {
        if (i == a.size())
            a.push_back(0);
        a[i] += carry + (i < b.size() ? b[i] : 0);
        carry = a[i] >= base;
        if (carry)  a[i] -= base;
    }
}


void multShortAndLong(lnum& a, unsigned long long b, unsigned long long base) {
    unsigned long long carry = 0;
    for (unsigned long long i = 0; i < a.size() || carry; ++i) {
        if (i == a.size())
            a.push_back(0);
        unsigned long long cur = carry + a[i] * 1ll * b;
        a[i] = (cur % base);
        carry = (cur / base);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}


void multLongNmbrs(const lnum& a, const lnum& b, lnum& c, unsigned long long base) {
    for (size_t i = 0; i < a.size(); ++i)
        for (unsigned long long j = 0, carry = 0; j < (unsigned long long)b.size() || carry; ++j) {
            unsigned long long cur = c[i + j] + a[i] * 1ll * (j < (unsigned long long)b.size() ? b[j] : 0) + carry;
            c[i + j] = (cur % base);
            carry = (cur / base);
        }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
}


void divLongToShort(lnum& a, unsigned long long b, unsigned long long& rem, unsigned long long base) {

    for (long long i = (long long)a.size() - 1; i >= 0; --i) {
        long long cur = a[i] + rem * 1ll * base;
        a[i] = (cur / b);
        rem = (cur % b);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}




int main() {
    unsigned long long p, k;
    cin >> p >> k;
    unsigned long long a, b;


    lnum arr;

    while (cin >> a >> b) {
        unsigned long long t = b * Pow(a, p - 1 - k, p) % p;
        arr.push_back(t);
    }

    lnum dec;
    lnum pow = { 1 };
    for (size_t i = 0; i < arr.size(); ++i) {
        lnum trash = pow;
        multShortAndLong(trash, arr[i], 10);
        sumLongNmbrs(dec, trash, 10);
        multShortAndLong(pow, p, 10);
    }

    lnum res64;

    lnum zero = { 0 };

    while (dec != zero) {
        unsigned long long rem = 0;
        divLongToShort(dec, 64, rem, 10);
        res64.push_back(rem);
    }

    for (size_t i = 0; i < res64.size(); ++i) {
        cout << intToChar(res64[i]);
    }
    return 0;
}
