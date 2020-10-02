long long mul_mod(long long a, long long b, const long long MOD) {
    return b ? (mul_mod(a * 2, b / 2, MOD) + (b & 1 ? a : 0)) % MOD : 0;
}

long long bpow_mod(long long a, long long b, const long long MOD) {
    return (b ? bpow_mod(a * a % MOD, b / 2, MOD) * (b & 1 ? a : 1) : 1) % MOD;
}

long long inv_mod(long long a, const long long MOD) {
    return bpow_mod(a, MOD - 2, MOD);
}

vector<long long> MODS = {MOD};

template <int kind = 0, int fast = 0 >
class mint {
public:
    long long v;

    mint() : v(0) {
    }

    mint(long long v)
    : v(fast == 0 ? (v < 0 ? (v % MODS[kind] + MODS[kind]) % MODS[kind]
    : (v >= MODS[kind] ? v % MODS[kind] : v))
    : (v)) {
    }

    long long get_mod() {
        return MODS[kind];
    }

    long long get_val() {
        return v;
    }

    void take_mod() {
        v %= MODS[kind];
    }
};
template <int kind, int fast>
ostream& operator<<(ostream& os, const mint<kind, fast>& x) {
    return os << (x.v % MODS[kind] + MODS[kind]) % MODS[kind];
}

template <int kind, int fast, int fast2>
bool operator==(mint<kind, fast>& a, mint<kind, fast2> b) {
    return a.v == b.v;
}

template <int kind, int fast, int fast2>
mint<kind, fast>& operator+=(mint<kind, fast>& a, mint<kind, fast2> b) {
    return a = a.v + b.v;
}

template <int kind>
mint<kind>& operator-=(mint<kind>& a, mint<kind> b) {
    return a = a.v - b.v;
}

template <int kind>
mint<kind>& operator*=(mint<kind>& a, mint<kind> b) {
    return a = a.v * b.v;
}

template <int kind>
mint<kind>& operator/=(mint<kind>& a, mint<kind> b) {
    return a = a.v * inv_mod(b.v, a.get_mod());
}

template <int kind, int fast, int fast2>
mint<kind, fast> operator+(mint<kind, fast> a, mint<kind, fast2> b) {
    return a += b;
}

template <int kind>
mint<kind> operator-(mint<kind> a, mint<kind> b) {
    return a -= b;
}

template <int kind>
mint<kind> operator*(mint<kind> a, mint<kind> b) {
    return a *= b;
}

template <int kind>
mint<kind> operator/(mint<kind> a, mint<kind> b) {
    return a /= b;
}

template <int kind, int fast>
mint<kind, fast>& operator+=(mint<kind, fast>& a, long long b) {
    return a = a.v + b;
}

template <int kind>
mint<kind>& operator-=(mint<kind>& a, long long b) {
    return a = a.v - b;
}

template <int kind>
mint<kind>& operator*=(mint<kind>& a, long long b) {
    return a = a.v * b;
}

template <int kind>
mint<kind>& operator/=(mint<kind>& a, long long b) {
    return a = a.v * inv_mod(b, a.get_mod());
}

template <int kind, int fast>
mint<kind, fast> operator+(mint<kind, fast> a, long long b) {
    return a += b;
}

template <int kind>
mint<kind> operator-(mint<kind> a, long long b) {
    return a -= b;
}

template <int kind>
mint<kind> operator*(mint<kind> a, long long b) {
    return a *= b;
}

template <int kind>
mint<kind> operator/(mint<kind> a, long long b) {
    return a /= b;
}

//デフォルトは法がMODS[0] (mint<>)
//MODSに要素を追加してmint<1>みたいな感じで呼べばok