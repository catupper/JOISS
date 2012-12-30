#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<long long, long long> P;
#define MOD 1000000007
long long comb[1050000], two_table[1050000];

P gcd(long long x, long long y){
    if(y == 0)return P(1, 0);
    P tmp = gcd(y, x % y);    
    return P(tmp.second, tmp.first - (x / y) * tmp.second);
}

long long rev(long long x){
    long long res = gcd(x, MOD).first;
    res %= MOD;
    res += MOD;
    return res % MOD;
}

void set_comb(long long x){
    comb[0] = 1;
    for(long long i = 1;i <= x;i++){
	comb[i] = (comb[i - 1] * (x - i + 1)) % MOD;
	comb[i] = (comb[i] * rev(i)) % MOD;
    }
}

long long two(long long x){
    if(two_table[x] != -1)return two_table[x];
    two_table[0] = 2;
    for(int i = 1;i <= x;i++){
	two_table[i] = two_table[i - 1] * two_table[i - 1];
	two_table[i] += MOD;
	two_table[i] %= MOD;
    }
    return two_table[x];
}

int main(){
    long long n, k;
    fill(two_table, two_table + 1050000, -1);
    cin >> n >> k;
    two(n);
    long long res = 1, x = 0;
    for(long long i = 1;i <= x;i++){
        res *= (x - i + 1);res %= MOD;
	res *= rev(i);res %= MOD;
    }
    n -= k;
    x -= !n;
    set_comb(n);
    for(long long i = 0;i <= n;i++){
	if(i % 2 == 0)
	    x += (comb[i] * two(n - i)) % MOD;
	else
	    x -= (comb[i] * two(n - i)) % MOD;
	x %= MOD;
    }
    res *= x;
    res %= MOD;
    res += MOD;
    cout << res % MOD << endl;    
}
