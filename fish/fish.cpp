#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;
typedef pair<int, char> FISH;
typedef pair<int, int> P;
typedef pair<int, P> TRI;
int bitg[500050], bitb[500050], couple[500050];
FISH fish[500050];
vector<P>  pairs;
int main(){
  cin >> n ;
  for(int i = 0;i < n;i++){
    cin >> fish[i].first >> fish[i].second;
  }
  sort(fish, fish + n);
  int right = 0;
  for(int i = 0;i < n;i++){
    while(right + 1 < n && fish[right + 1].first < fish[i].first){
      right++;
      if(fish[i].second == 'R')r++;
      if(fish[i].second == 'G')g++;
      if(fish[i].second == 'B')b++;
    }
    groups.push_back(TRI(r, P(g, b)));
    if(right + 1 >= n)break;
    if(fish[i].second == 'R')r--;
    if(fish[i].second == 'G')g--;
    if(fish[i].second == 'B')b--;
  }
  sort(groups.begin(), groups.end(), greater<TRI>);
  for(int i = 0;i < groups.size();i++){
    int pos = lowwer_bound(groups.begin(), groups.end()) - groups.begin();
    
  }
}
