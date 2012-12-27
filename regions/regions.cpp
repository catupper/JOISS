#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#define INF (1<< 30)
using namespace std;

vector<pair<int, int> > citys[30002];


pair<int, int> solve(int rad, int root, int from){
  pair<int, int> res = make_pair(1, 0);
  int child[citys[root].size()];
  for(int i = 0;i < citys[root].size();i++){
    if(citys[root][i].first == from){
      child[i] = INF;
      continue;
    }
    pair<int, int> tmp = solve(rad, citys[root][i].first, root);
    child[i] = tmp.second + citys[root][i].second;
    res.first += tmp.first;
  }
  sort(child, child + citys[root].size());
  if(child[0] <= rad)res.first--, res.second = child[0];
  for(int i = 1;i < citys[root].size() - 1;i++){
    if(child[i] + child[i - 1] > rad)break;
    res.first--;
    res.second = child[i];
  }
  return res;
}


int main(){
  int m, n, a, b, c;
  scanf("%d%d", &n, &m);
  for(int i = 0;i < n - 1;i++){
    scanf("%d%d%d", &a, &b, &c);
    citys[a].push_back(make_pair(b, c));
    citys[b].push_back(make_pair(a, c));
  }
  int top = 30002, bot = 0;
  cout << solve(254, 1, 0).first << endl;
  while(top - bot > 1){
    int mid = (top + bot) / 2;
    if(solve(mid, 1, 0).first <= m)
      top = mid;
    else
      bot = mid;
  }
  printf("%d\n", top);
}
