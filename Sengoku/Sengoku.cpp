#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int main(){
  int l, n, x, y;
  long long int ans = 0;
  set<int> left, right;
  vector<int> leftupeven, leftupodd, rightupeven, rightupodd;
  scanf("%d%d", &l, &n);
  for(int i = 0;i < n;i++){
    scanf("%d%d", &x, &y);
    if(left.find(x - y) == left.end()){
      if((x - y) % 2 == 0)
	leftupeven.push_back(x - y);
      if((x - y) % 2 == 1)
	leftupodd.push_back(x - y);
    }
    if(right.find(x + y) == right.end()){
      if((x + y) % 2 == 0)
	rightupeven.push_back(x + y);
      if((x + y) % 2 == 1)
	rightupodd.push_back(x + y);
    }
    left.insert(x - y);
    right.insert(x + y);
  }
  sort(leftupeven.begin(), leftupeven.end());
  sort(leftupodd.begin(), leftupodd.end());
  sort(rightupeven.begin(), rightupeven.end());
  sort(rightupodd.begin(), rightupodd.end());
  
  vector<int>::iterator it;
  for(it = leftupeven.begin();it != leftupeven.end();it++){
    ans += l - abs(*it);
  }
  for(it = leftupodd.begin();it != leftupodd.end();it++){
    ans += l - abs(*it);
  }
  for(it = rightupeven.begin();it != rightupeven.end();it++){
    ans += l - abs(l - *it);
    if(*it < l){
      ans -= upper_bound(leftupeven.begin(), leftupeven.end(), *it) - lower_bound(leftupeven.begin(), leftupeven.end(), -*it);
    }
    else{
      ans -= upper_bound(leftupeven.begin(), leftupeven.end(), (l - 1) * 2 - *it) - lower_bound(leftupeven.begin(), leftupeven.end(), *it - (l - 1) * 2 );
    }
  }
  for(it = rightupodd.begin();it != rightupodd.end();it++){
    ans += l - abs(l - *it);
    if(*it < l){
      ans -= upper_bound(leftupodd.begin(), leftupodd.end(), *it) - lower_bound(leftupodd.begin(), leftupodd.end(), -*it);
    }
    else{
      ans -= upper_bound(leftupodd.begin(), leftupodd.end(), (l - 1) * 2 - *it) - lower_bound(leftupodd.begin(), leftupodd.end(), *it - (l - 1) * 2 );
    }
  }
  printf("%lld\n", ans);
  return 0;
}
