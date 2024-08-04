class Hashing {
    using ul = unsigned long long;
public:
    // mod 2^61-1を計算する関数
    ul calc_mod(ul x);
    // a*b mod 2^61-1を返す関数(最後にmodを取る)
    ul mul(ul a, ul b);
    // ハッシュ列をつくる
    vector<ul> make(const string& s);
    // ハッシュ列から値を取得(開区間)
    ul get(const vector<ul>& hash, ul l, ul r);
    // base^a mod 2^61-1を計算
    ul pow(ul a);

    Hashing();
private:
    const ul MASK30 = (1ULL << 30) - 1;
    const ul MASK31 = (1ULL << 31) - 1;
    const ul MOD = (1ULL << 61) - 1;
    const ul MASK61 = MOD;
    std::random_device seed_gen;
    std::mt19937_64 engine;
    ul base;
    const int base_area = 1e6 + 9;
    vector<ul> B;
};

// コンストラクタの定義
Hashing::Hashing() : engine(seed_gen()), base(engine() % MOD), B(base_area) {
    B[0] = 1;
    for (int i = 1; i < base_area; i++) {
        B[i] = mul(B[i - 1], base);
    }
}

Hashing::ul Hashing::calc_mod(ul x) {
    ul xu = x >> 61;
    ul xd = x & MASK61;
    ul res = xu + xd;
    if (res >= MOD) res -= MOD;
    return res;
}

Hashing::ul Hashing::mul(ul a, ul b) {
    ul au = a >> 31;
    ul ad = a & MASK31;
    ul bu = b >> 31;
    ul bd = b & MASK31;
    ul mid = ad * bu + au * bd;
    ul midu = mid >> 30;
    ul midd = mid & MASK30;
    return calc_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
}

vector<Hashing::ul> Hashing::make(const string& s) {
    vector<ul> hash(s.size() + 1);
    hash[0] = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        hash[i + 1] = calc_mod(mul(hash[i], base) + s[i]);
    }
    return hash;
}

Hashing::ul Hashing::get(const vector<ul>& hash, ul l, ul r) {
    return calc_mod(hash[r] + MOD - mul(hash[l], B[r - l]));
}

Hashing::ul Hashing::pow(ul a) {
    ul res = 1;
    ul b = base;
    while (a) {
        if (a & 1) res = mul(res, b);
        b = mul(b, b);
        a >>= 1;
    }
    return res;
}
