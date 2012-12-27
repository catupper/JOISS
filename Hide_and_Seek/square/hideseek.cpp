#include<stdio.h>
#include<algorithm>
using namespace std;
typedef pair<pair<int, int>, int> Wall;

Wall wall[50000];
int pt[317][317];
int ptall[317];
int searc = 1;
pair<int, int> maxind[317];
pair<int, int> ans[50000];

int main(){
  int n, m;
  for(int i = 0;i < 317;i++){
    maxind[i].first = 0;
    maxind[i].second = i * 317;
  }
  for(int i = 0;i < 50000;i++){
    ans[i].first = -1;
    ans[i].second = -1;
  }

  scanf("%d%d", &n, &m);
  for(int i = 0;i < n;i++){
    scanf("%d%d%d", &wall[i].first.second, &wall[i].first.first, &wall[i].second);
  }
  sort(wall, wall + n);
  for(int i = 0;i < n;i++){
    Wall tmp = wall[i];
    int l = tmp.first.second;
    int r = tmp.first.first;
    int s = tmp.second;
    while(l % 317 != 0 && s > 0){
      pt[l / 317][l % 317]++;
      if(pt[l / 317][l % 317] + ptall[l / 317] > maxind[l / 317].first){
	maxind[l / 317].first = pt[l / 317][l % 317] + ptall[l / 317];
	maxind[l / 317].second = l;
      }
      if(maxind[l / 317].first == searc){
	ans[searc].first = maxind[l / 317].second;
	ans[searc].second = r;
	searc++;
      }
      s--;
      l++;
    }
    while(s >= 317){
      ptall[l / 317]++;
      maxind[l / 317].first++;
      if(maxind[l / 317].first == searc){
	ans[searc].first = maxind[l / 317].second;
	ans[searc].second = r;
	searc++;
      }
      s -= 317;
      l += 317;
    }
    while(s > 0){
      pt[l / 317][l % 317]++;
      if(pt[l / 317][l % 317] + ptall[l / 317]> maxind[l / 317].first){
	maxind[l / 317].first = pt[l / 317][l % 317] + ptall[l / 317];
	maxind[l / 317].second = l;
      }
      if(maxind[l / 317].first == searc){
	ans[searc].first = maxind[l / 317].second;
	ans[searc].second = r;
	searc++;
      }
      s--;
      l++;
    }
  }

  for(int i = 0;i < m;i++){
    int tmp;
    scanf("%d", &tmp);
    printf("%d %d\n", ans[tmp + 1].first, ans[tmp + 1].second);
  }
  return 0;
}
