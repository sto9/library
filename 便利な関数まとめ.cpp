inline ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

inline ll mod(ll a, ll b)
{
    if (a >= 0)
        return a % b;
    else
        return (b - (-a) % b) % b;
}

inline ll CEIL(ll a, ll b)
{
    return (a + b - 1) / b;
}

inline int CEIL(int a, int b)
{
    return (a + b - 1) / b;
}

inline ld dist(ld &x1, ld &y1, ld &x2, ld &y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void make_primes(set<ll> &primes, int s = 100010)
{

    for (int i = 2; i <= s; ++i)
    {
        bool is_prime = true;
        for (auto p : primes)
        {
            if (i % p == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            primes.insert(i);
    }
}

inline ll digit_sum(ll a, ll b = 10)
{
    ll sum = 0;
    do
    {
        sum += a % b;
    } while (a /= b);
    return sum;
}

inline ll div_down(ll a, ll d)
{
    if (a < 0)
        return -(CEIL(-a, d));
    else
        return (a / d);
}

inline ll div_up(ll a, ll d)
{
    if (a < 0)
        return -((-a) / d);
    else
        return CEIL(a, d);
}

void add(int (&a)[100010], int (&b)[100010], int (&res)[100010], int &len)
{

    int up_num = 0;

    rep(i, 100005)
    {
        res[i] = (a[i] + b[i] + up_num) % 10;
        up_num = (a[i] + b[i] + up_num) / 10;
        if (res[i] != 0)
            len = i + 1;
    }
}

void lambda()
{

    auto simulate = [&](ll x) {

    };

    auto binary_search = [&]() {
        ll lo = 0, hi = INF;
        while (hi - lo > 1)
        {
            ll mi = (lo + hi) / 2;
            if (simulate(mi))
                hi = mi;
            else
                lo = mi;
        }
        return hi;
    };

    auto binary_search = [&]() {
        ll lo = 0, hi = INF;
        while (hi - lo > 1)
        {
            ll mi = (lo + hi) / 2;
            if (simulate(mi))
                lo = mi;
            else
                hi = mi;
        }
        return lo;
    };

    //long long int 用

    auto binary_search = [&]() {
        ll lo = 0, hi = LINF;
        while (hi - lo > 1)
        {
            ll mi = (lo + hi) / 2;
            if (simulate(mi))
                hi = mi;
            else
                lo = mi;
        }
        return hi;
    };

    auto binary_search = [&]() {
        ll lo = 0, hi = LINF;
        while (hi - lo > 1)
        {
            ll mi = (lo + hi) / 2;
            if (simulate(mi))
                lo = mi;
            else
                hi = mi;
        }
        return lo;
    };

    //条件を満たすギリギリを返す

    //1つ目は後半が条件を満たすとき
    //left は「常に」条件を満たさない
    //right は「常に」条件を満たす

    //2つ目は前半が条件を満たすとき
    //left は「常に」条件を満たす
    //right は「常に」条件を満たさない

    auto f = [&](const ld x) {
        return x;
    };

    auto ternary_search = [&]() {
        ld left = 0, right = LINF;

        rep(simulate_times, 300)
        {
            ld t1 = (2.0 * left + right) / 3.0;
            ld t2 = (left + 2.0 * right) / 3.0;
            if (f(t1) > f(t2))
                left = t1;
            else
                right = t2;
        }

        cout << f(left) << endl;
    };

    ll csum[200010];
    csum[0] = 0;
    rep(i, n) csum[i + 1] = csum[i] + a[i];

    //[l, r)の和
    auto sum = [&](ll L, ll R) {
        return csum[R] - csum[L];
    };
}

vector<string> split(string s, char c)
{
    vector<string> v;
    string t = "";
    auto v_push = [&](string sp) {
        if (sp == "")
            return;
        v.push_back(sp);
    };
    rep(i, s.length())
    {
        if (s[i] == c)
        {
            v_push(t);
            t = "";
        }
        else if (i == (int)s.length() - 1)
        {
            t.push_back(s[i]);
            v_push(t);
        }
        else
        {
            t.push_back(s[i]);
        }
    }
    return v;
}

void numeration_add(int N, vector<int> &pattern, int i)
{ //N進法
    if (pattern[i] != N - 1)
        pattern[i]++;
    else
    {
        pattern[i] = 0;
        numeration_add(N, pattern, i + 1);
    }
}

#include <boost/multiprecision/cpp_int.hpp>
using multiInt = boost::multiprecision::cpp_int;