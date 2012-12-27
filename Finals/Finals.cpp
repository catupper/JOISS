#include<stdio.h>
#include<queue>
#include<map>
#include<functional>
#include<algorithm>
using namespace std;
typedef pair<int,pair<int,int> > Road;

priority_queue<Road, vector<Road>, greater<Road> > roads;

int u[100001];

int unin(int x){
  if(u[x] == x)return x;
  return u[x] = unin(u[x]);
}

int main(){
  int n, m, k, a, b, c, res = 0;
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 0;i < n;i++)u[i] = i;
  for(int i = 0;i < m;i++){
    scanf("%d%d%d", &a, &b, &c);
    roads.push(make_pair(c, make_pair(a, b)));
  }
  while(n != k){
    Road tmp = roads.top(); roads.pop();
    if(unin(tmp.second.first) == unin(tmp.second.second))continue;
    u[tmp.second.first] = u[tmp.second.second];
    res += tmp.first;
    n--;
  }
  printf("%d\n", res);
  return 0;
}
