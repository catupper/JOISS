#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;
typedef pair<long long, long long> P;
void rev(vector<P> &x){
  vector<P> res;
  for(long long i = (long long)x.size();i--;){
    res.push_back(x[i]);
  }
  for(long long i = 1;i < res.size();i++){
    res[i].first += res[i - 1].first;
  }
  x = res;
}

void asshuku(vector<P> &a, vector<P> &b, vector<long long> &res){
  long long p = 0;
  res.push_back(1);
  for(long long i = 0;i < a.size();i++){
    res.push_back(a[i].first);
    res.push_back(a[i].first + 1);
    res.push_back(a[i].first + 2);
  }
  for(long long i = 0;i < b.size();i++){
    res.push_back(b[i].first);
    res.push_back(b[i].first + 1);
    res.push_back(b[i].first + 2);
  }
  sort(res.begin(), res.end());
  vector<long long>::iterator it = unique(res.begin(), res.end());
  res.erase(it, res.end());
}

void convert(vector<P> &a, vector<long long> &comp){
  vector<P> res;
  vector<P>::iterator it = a.begin();
  for(long long i = 0;i < comp.size();i++){
    if(it == a.end()){
      res.push_back(P(comp[i], 0));
    }
    else{
      res.push_back(P(comp[i], (*it).second));
      if((*it).first == comp[i])it++;
    }
  }
  a = res;
}

void add(vector<P> &a, vector<P> &b){
  long long k = 0, n = (long long)a.size();
  for(long long i = 0;i < n;i++){
    a[i].second += b[i].second + k;
    k = a[i].second / 10;
    a[i].second %= 10;
  }
  if(k == 1)
    a.push_back(P(a[n].first + 1, 1));
}

void zip(vector<P> &a){
  vector<P> res;
  long long last = a[0].second, l = 0, r = a[0].first;
  for(long long i = 1;i < a.size() - 1;i++){
    if(last != a[i].second){
      res.push_back(P(r - l, last));
      last = a[i].second;
      l = r;
      r = a[i].first;
    }
    else{
      r = a[i].first;
    }
  }
  if(last != 0)
    res.push_back(P(r - l, last));
  a.clear();
  for(long long i = (long long)res.size();i--;)
    a.push_back(res[i]);
}

int main(){
  vector<P> a, b;
  vector<long long> comp;
  long long p, q, x;
  cin >> x;
  for(long long i = 0;i < x;i++){
    cin >> p >> q;
    a.push_back(P(q, p));
  }

  cin >> x;
  for(long long i = 0;i < x;i++){
    cin >> p >> q;
    b.push_back(P(q, p));
  }
  rev(a);
  rev(b);
  asshuku(a, b, comp);
  convert(a, comp);  
  convert(b, comp);
  add(a, b);
  zip(a);
  cout << a.size() << endl;
  for(long long i = 0;i < a.size();i++){
    cout << a[i].second << ' ' <<  a[i].first << endl;
  }
  return 0;
}
