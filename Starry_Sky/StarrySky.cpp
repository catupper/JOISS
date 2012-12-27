#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<long long , long long > P;
typedef pair<P, long long > STAR;

STAR stars[4200];
vector<long long > lights;
set<long long> asshuku;
map<long long, long long> zahyou;
long long  n, res, cnt;

struct segnode{
  segnode(){
    all = 0;
    r = 0;
    l = 0;
    maximum = 0;
  }
  long long  bottom, top, all, maximum;
  segnode *r, *l;
};
segnode* root ;
segnode  pointer[800000];
int pp = 0;

void add_segtree(long long  left, long long  right, segnode* r, long long  add){
  if(right < r->bottom || r->top < left)return;
  if(left <= r->bottom && r->top <= right)
    r->all += add;
  else{
    long long  mid = (r->bottom + r->top) / 2;
    if(mid == r->top)mid--;
    if(r->l == 0){
      r->l = pointer + (pp++);
      r->l->bottom = r->bottom;
      r->l->top = mid;
    }
    if(r->r == 0){
      r->r = pointer + (pp++);
      r->r->bottom = mid + 1;
      r->r->top = r->top;
    }
    add_segtree(left, right, r->l, add);
    add_segtree(left, right, r->r, add);
    r->maximum = max(r->l->maximum + r->l->all, r->r->maximum + r->r->all);
  }
}


long long  solve(long long  x){
  long long  res = 0;
  int r = 0, l = 0;
  queue<STAR> q;
  for(int i = 0;i < n;i++){
    if(stars[i].second != x)continue;
    while(stars[r].first.first < stars[i].first.first - x)r++;
    while(l < n && stars[i].first.first >= stars[l].first.first - x) l++;
    i = l;
    for(;r < l;r++){
      if(stars[r].second < x)continue;
      q.push(stars[r]);
      while(!q.empty() && q.front().first.first  < stars[r].first.first - x){
	STAR tmp = q.front();q.pop();
	map<long long, long long>::iterator it = zahyou.upper_bound(tmp.first.second + x);
	add_segtree(zahyou[tmp.first.second], (*--it).second, root, -1);
      }
      map<long long, long long>::iterator it = zahyou.upper_bound(stars[r].first.second + x);
      add_segtree(zahyou[stars[r].first.second], (*--it).second, root, 1);
      res = max(res, root -> all + root -> maximum);
    }
    r = i;
  }
  while(!q.empty()){
    STAR tmp = q.front();q.pop();
    map<long long, long long>::iterator it = zahyou.upper_bound(tmp.first.second + x);
    add_segtree(zahyou[tmp.first.second], (*--it).second, root, -1);
  }  
  return res;
}


int main(){
  cin >> n;
  for(long long i = 0;i < n;i++){
    cin >> stars[i].first.first >> stars[i].first.second >> stars[i].second;    
    lights.push_back(stars[i].second);
    asshuku.insert(stars[i].first.second);
  }
  sort(stars, stars + n);
  sort(lights.begin(), lights.end());
  vector<long long>::iterator it = lights.end();
  set<long long>::iterator y = asshuku.begin();
  for(int i = 0;y != asshuku.end();i++,y++){
    zahyou[*y] = i;
  }
  root = pointer + (pp++);
  root->bottom = 0;
  root->top = asshuku.size() - 1;
  while(true){
    it--;
    res = max(res, solve(*it));
    if(it == lights.begin())break;
  }
  cout << res << endl;
  return 0;
}
