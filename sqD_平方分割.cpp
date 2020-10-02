

struct SqrtDecomposition
{
    constexpr int sqrtN = 512;

    int N, K; //N…配列の要素数 K…bucketの要素数
    //bucketの幅はsqrtN
    vector<int> data;
    vector<int> bucket;

    SqrtDecomposition(int n)
    {
        N = n;
        K = (N + sqrtN - 1) / sqrtN;
        data.assign(K * sqrtN, 0);
        bucket.assign(K, 0);
    }

    void setValue()
    { //初期化

        rep(k, K)
        {
            int sum = 0;

            rep(i, sqrtN)
            {
                sum += data[k * sqrtN + i];
            }
            bucket[k] = sum;
        }
    }

    void changeValue(int x, int y)
    { //x番目にyを可算
        int k = x / sqrtN;
        data[x] += y;
        int sum = 0;

        REP(i, k * sqrtN, (k + 1) * sqrtN)
        {
            sum += data[i];
        }
        bucket[k] = sum;
    }

    int getValue(int x, int y)
    { //[x, y)
        int sum = 0;

        rep(k, K)
        {
            int l = k * sqrtN, r = (k + 1) * sqrtN;
            if (r <= x || y <= l)
                continue;
            if (x <= l && r <= y)
            {
                sum += bucket[k];
            }
            else
            {
                REP(i, max(x, l), min(y, r))
                sum += data[i];
            }
        }
        return sum;
    }
};