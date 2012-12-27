#include<cstdio>
#include<algorithm>
using namespace std;
#define MOD 1234567

int dp[500005];
int stair[500005];
int ruisekiwa[500005];
int n, p;
int main(){
  scanf("%d%d", &n, &p);
  for(int i = 1;i <= n;i++){
    scanf("%d", stair + i);
    ruisekiwa[i] = ruisekiwa[i - 1] + stair[i];
  }
  dp[0] = 1;
  for(int i = 1;i <= n;i++){
    dp[i] = dp[i - 1] * 2;
    if(ruisekiwa[i] > p)
      dp[i] -= dp[lower_bound(ruisekiwa, ruisekiwa + n + 1, ruisekiwa[i] - p) - ruisekiwa - 1];
    dp[i] += MOD;
    dp[i] %= MOD;
  }
  printf("%d\n", dp[n] - dp[n - 1]);
  return 0;
}
