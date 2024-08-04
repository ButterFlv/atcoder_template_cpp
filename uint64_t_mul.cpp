using ul = unsigned long long;
const ul MASK30 = (1ULL << 30) - 1;
const ul MASK31 = (1ULL << 31) - 1;
const ul MOD = (1ULL << 61) - 1;
const ul MASK61 = MOD;

//mod 2^61-1を計算する関数
ul CalcMod(ul x)
{
    ul xu = x >> 61;
    ul xd = x & MASK61;
    ul res = xu + xd;
    if (res >= MOD) res -= MOD;
    return res;
}

//a*b mod 2^61-1を返す関数(最後にModを取る)
ul Mul(ul a, ul b)
{
    ul au = a >> 31;
    ul ad = a & MASK31;
    ul bu = b >> 31;
    ul bd = b & MASK31;
    ul mid = ad * bu + au * bd;
    ul midu = mid >> 30;
    ul midd = mid & MASK30;
    return CalcMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
}
