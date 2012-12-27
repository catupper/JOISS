#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<functional>
#include<algorithm>
using namespace std;
typedef pair<int, int> P;

vector<P> dragons;
vector<int> tate, yoko;

bool comp_y(const P &x, const P &y){
  if(x.second == y.second)
    return x.first < y.first;
  return x.second < y.second;
}

bool comp_y_great(const P &x, const P &y){
  if(x.second == y.second)
    return x.first > y.first;
  return x.second > y.second;
}

long long left(){
  long long res = 0;
  int last = -1;
  sort(yoko.begin(), yoko.end());
  sort(dragons.begin(), dragons.end());
  for(int i = 0;i < dragons.size();i++){
    if(last == dragons[i].first)continue;
    last = dragons[i].first;
    if(dragons[i].second <= 2)continue;
    res = max(res, last - 1 - (lower_bound(yoko.begin(), yoko.end(), dragons[i].second) - yoko.begin()));
  }
  return res;
}

long long right(){
  long long res = 0;
  int last = -1;
  sort(tate.begin(), tate.end(), greater<int>);
  sort(dragons.begin(), dragons.end(), greater<P>);
  for(int i = 0;i < dragons.size();i++){
    if(last == dragons[i].first)continue;
    last = dragons[i].first;
    if(dragons[i].second >= w - 1)continue;
    res = max(res, w - last - (lower_bound(yoko.begin(), yoko.end(), dragons[i].second, greter<int>) - yoko.begin()));
  }
  return res;
}

long long up(){
  long long res = 0;
  int last = -1;
  sort(tate.begin(), tate.end());
  sort(dragons.begin(), dragons.end(), comp_y);
  for(int i = 0;i < dragons.size();i++){
    if(last == dragons[i].second)continue;
    last = dragons[i].second;
    if(dragons[i].second <= 2)continue;
    res = max(res, last - 1 - (lower_bound(tate.begin(), tate.end(), dragons[i].first) - tate.begin()));
  }
  return res;
}

long long down(){
  long long res = 0;
  int last = -1;
  sort(tate.begin(), tate.end(), greater<int>);
  sort(dragons.begin(), dragons.end(), comp_y_great);
  for(int i = 0;i < dragons.size();i++){
    if(last == dragons[i].first)continue;
    last = dragons[i].first;
    if(dragons[i].second >= h - 1)continue;
    res = max(res, h - last - (lower_bound(yoko.begin(), yoko.end(), dragons[i].first, greater<int>) - yoko.begin()));
  }
  return res;
}

long long lu(){
  long long res = 0;
  int last = -1;
  
}

void my_unique(vector<int> *x){
  srot(x->begin(), x->end());
  vector<int>::iterator it = unique(x->begin(), x->end());
  x->erase(it, x->end());
}

int main(){
  long long res = 0;
  cin >> h >> w >> n;
  for(int i = 0;i < n;i++){
    cin >> x >> y;
    tate.push_back(x);
    yoko.push_back(y);
    dragons.push_back(P(x, y));
  }
  my_unique(&tate);
  my_unique(&yoko);
  res = max(res, left());
  res = max(res, right());
  res = max(res, up());
  res = max(res, down());
  res = max(res, lu());
  res = max(res, ld());
  res = max(res, ru());
  res = max(res, rd());
  cout << res + (h - tate.size()) * (w - yoko.size()) << endl;
}
