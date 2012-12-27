#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
#define INF (1 << 29)
int dp[160000], n;
string str, tmp;

struct trienode{
  trienode(){
    flag['A'] = 0;
    flag['G'] = 0;
    flag['C'] = 0;
    flag['T'] = 0;
    leaf = false;
  }
  map<char, trienode*> flag;
  bool leaf;
};
trienode *root = new trienode;

void add(string &str, int l = 0, trienode *r = root){
  if(l == str.size()){
    r->leaf = true;
  }
  else{
    if(r->flag[str[l]] == 0)
      r->flag[str[l]] = new trienode;
    add(str, l + 1, r->flag[str[l]]);
  }
}

int main(){
  cin >> n;
  cin >> str;
  for(int i = 0;i < n;i++){
    cin >> tmp;
    add(tmp);
  }
  fill(dp, dp + 160000, INF);
  dp[0] = 0;
  for(int i = 0;i < str.size();i++){
    tmp = "";
    int j = i, last = -1;
    trienode* tmp = root;
    while(j < str.size() && tmp->flag[str[j]] != 0){
      tmp = tmp->flag[str[j]];
      if(tmp->leaf)last = j;
      j++;
    }
    while(last > i){
      dp[last] = min(dp[last], dp[i] + 1);
      last--;
    }
  }
  dp[0] = 1;
  cout << dp[str.size() - 1] << endl;
}
