#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<int, int> P;

P book[105000];

int n;
long long bit[105000], dp[105000], res, sum;

void setval(int x, long long val){
    while(x < 104000){
	bit[x] = max(val, bit[x]);
	x += x & -x;
    }
}

long long maximum(int x){
    long long res = 0;
    while(x){
	res = max(res, bit[x]);
	x -= x & -x;
    }
    return res;
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> book[i].first;
	sum += book[i].first;
    }
    for(int i = 0;i < n;i++){
	cin >> book[i].second;
    }
    for(int i = 0;i < n;i++){
	dp[book[i].first] = max(dp[book[i].first], maximum(book[i].first - 1) + book[i].second);
	setval(book[i].first, dp[book[i].first]);
	res = max(res, dp[book[i].first]);
    }
    cout << (sum - res) * 2 << endl;
    return 0;
}
