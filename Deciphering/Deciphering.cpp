#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MOD 10000000
int l, m, dp[30];
char a, b;
bool no[30][30];
string str;

int main(){
    cin >> l;
    cin >> str;
    cin >> m;
    dp[26] = 1;
    for(int i = 0;i < m;i++){
	scanf(" %c %c", &a, &b);
	no[a - 'A'][b - 'A'] = true;
    }
    for(int i = 0;i < str.size();i++){
	int x = str[i] - 'A';
	int res = 0;
	for(int j = 0;j <= 26;j++){
	    if(!no[j][x]){
		res += dp[j];
	    }
	}
	dp[x] = res % MOD;
    }
    int res = 0;
    for(int i = 0;i < 26;i++)
	res += dp[i];
    res %= MOD;
    cout << (res + MOD) % MOD<< endl;
}
