#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int m, b;
multiset<int> apples;

struct segnode{
  segnode(int b, int t){
    bottom = b;
    top = t;
    all = 0;
    part = 0;
    r = 0;
    l = 0;
  }
  int bottom, top, all, part;
  segnode* r,* l;
};

segnode* root = new segnode(0, 1 << 30);

void add_apple(int x, int y, segnode* r, int add){
  if(y < r->bottom || r->top < x)return;
  if(x <= r->bottom && r->top <= y){
    r->all += add;
  }
  else{
    int mid = (r->bottom + r->top) / 2;
    if(mid == r->top)mid--;
    if(r->l == 0){
      r->l = new segnode(r->bottom, mid);
    }
    if(r->r == 0){
      r->r = new segnode(mid + 1, r->top);
    }
    add_apple(x, y, r->l, add);
    add_apple(x, y, r->r, add);
    r->part = max(r->l->all + r->l->part, r->r->all + r->r->part);
  }
}

int solve(int x, segnode* r){
  if(r->all + r->part < x){
    return -1;
  }
  if(r->bottom == r->top)
    return r->top;
  x -= r->all;
  if(r->r == 0 && r->l == 0)
    return r -> top;
  if(r->r != 0 && r->r->all + r->r->part >= x)
    return solve(x, r->r);
  else
    return solve(x, r->l);
}

void erase_interval(int x, int y){
  x = *(apples.lower_bound(x));
  multiset<int>::iterator it = apples.upper_bound(x);
  vector<int> res;
  while(y && it != apples.end()){
    if(*it > x + b)break;
    add_apple(max(*it - b, 0), *it, root, -1);
    res.push_back(*it);
    apples.erase(it++);
    y--;
  }
  it = apples.lower_bound(x);
  while(y--){
    add_apple(max(*it - b, 0), *it, root, -1);
    cout << *it << ' ';
    apples.erase(it++);
  }
  vector<int>::iterator vit = res.begin();
  while(vit != res.end())
    cout << *vit++ << ' ';
  cout << endl;
}

int main(){
  char order;
  int num;
  cin >> m >> b;
  for(int i = 0;i < m - 1;i++){
    cin >> order >> num;
    if(order == 'A'){
      add_apple(max(num - b, 0), num, root, 1);
      apples.insert(num);
    }
    if(order == 'R'){
      int minimum = solve(num, root);
      if(minimum == -1)
	cout << "NO" << endl;
      else
	erase_interval(minimum, num);
    }
  }
  cin >> order;
  return 0;
}
