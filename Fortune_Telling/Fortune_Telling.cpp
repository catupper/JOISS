#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<long long, long long> P;
typedef pair<P, P> Q;

vector<long long> tbcomp, lrcomp;

struct segnode{
  segnode(){}
  void setting(int b, int t, int l, int r){
    bottom = b;
    top = t;
    left = l;
    right = r;
    fill = (tbcomp[t] - tbcomp[b]) * (lrcomp[r] - lrcomp[l]);
    real = 0;
    all = 0;
    part = 0;
    lu = ld = ru = rd = 0;
  }
  long long  bottom, top, all, part, right, left, fill, real;
  segnode *lu, *ld, *ru, *rd;
};

segnode pointers[500000], *root;
int pp = 0;
vector<Q> query;
void my_unique(vector<long long>* x){
  sort(x->begin(), x->end());
  vector<long long>::iterator e = unique(x->begin(), x->end());
  x->erase(e, x->end());
}

void seg_turn(int b, int t, int l, int r, segnode* root){
  if(t <= root->bottom || root->top <= b || r <= root->left  || root->right <= l){
    return;
  }
  if(b <= root->bottom && root->top <= t && l <= root->left && root->right <= r){
    root->all ^= 1;
    root->real = root->fill - root->real;
  }
  else{
    int lrmid = (root->left + root->right)/2, btmid = (root->bottom + root->top)/2;
    int bottom = root->bottom, top = root->top, left = root->left, right = root->right;
    if(root->lu == 0){
      root->lu = pointers + (pp++);
      root->lu->setting(bottom, btmid, left, lrmid);
    }
    if(root->ld == 0){
      root->ld = pointers + (pp++);
      root->ld->setting(btmid, top, left, lrmid);
    }
    if(root->ru == 0){
      root->ru = pointers + (pp++);
      root->ru->setting(bottom, btmid, lrmid, right);
    }
    if(root->rd == 0){
      root->rd = pointers + (pp++);
      root->rd->setting(btmid, top, lrmid, right);
    }
    seg_turn(b, t, l, r, root->lu);
    seg_turn(b, t, l, r, root->ld);
    seg_turn(b, t, l, r, root->ru);
    seg_turn(b, t, l, r, root->rd);
    root->part = root->lu->real + root->ld->real + root->ru->real + root->rd->real;
    if(root->all == 1){
      root->real = root->fill - root->part;
    }
    else{
      root->real = root->part;
    }
  }
}



int main(){
  long long  m, n, k, a, b, c, d;
  cin >> m >> n >> k;
  for(int i = 0;i < k;i++){
    cin >> a >> b >> c >> d;
    query.push_back(Q(P(a, b), P(c, d)));
    tbcomp.push_back(a);
    tbcomp.push_back(a + 1);
    tbcomp.push_back(b);
    tbcomp.push_back(b + 1);
    lrcomp.push_back(c);
    lrcomp.push_back(c + 1);
    lrcomp.push_back(d);
    lrcomp.push_back(d + 1);
  }
  my_unique(&lrcomp);
  my_unique(&tbcomp);
  root = pointers + (pp++);
  root->setting(0, tbcomp.size() - 1, 0, lrcomp.size() - 1);
  for(int i = 0;i < k;i++){
    a = lower_bound(tbcomp.begin(), tbcomp.end(), query[i].first.first) - tbcomp.begin();
    b = upper_bound(tbcomp.begin(), tbcomp.end(), query[i].first.second) - tbcomp.begin();
    c = lower_bound(lrcomp.begin(), lrcomp.end(), query[i].second.first) - lrcomp.begin();
    d = upper_bound(lrcomp.begin(), lrcomp.end(), query[i].second.second) - lrcomp.begin();
    seg_turn(a, b, c, d, root);
  }
  cout << n * m - root->real << endl;
  return 0;
}
