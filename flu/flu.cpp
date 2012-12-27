#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define sq(x) ((x) * (x))

vector<int> comp[1001][1001];
queue<int> q;
int xs[] = {-1, -1, 0, 1, 1, 1, 0, -1, 0}, ys[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
int d, p[105000][2], n, m, flu[105000], k;

bool near(int x, int y){
  return sq(d) >= sq(p[x][0] - p[y][0]) + sq(p[x][1] - p[y][1]);
}

void spread(int day){
  for(int i = (int)q.size();i--;){
    int tmp = q.front();q.pop();
    int x = p[tmp][0] / d, y = p[tmp][1] / d;
    for(int i = 0;i < 9;i++){
      x += xs[i], y += ys[i];
      if(0 <= x && 0 <= y){
	vector<int>::iterator it = comp[x][y].begin();
	for(;it != comp[x][y].end();it++){
	  if(flu[*it] != -1)continue;
	  if(near(*it, tmp)){
	    flu[*it] = day;
	    q.push(*it);
	  }
	}
      }
      x -= xs[i], y -= ys[i];
    }
  }
}

int solve(int limit){
  int res = 0;
  for(int i = 0;i < n;i++){
    if(limit < flu[i])res++;
  }
  return res;
}

int main(){
  cin >> n >> m >> d >> k;
  for(int i = 0;i < n;i++){
    flu[i] = -1;
    cin >> p[i][0] >> p[i][1];
    comp[p[i][0] / d][p[i][1] / d].push_back(i);
  }
  flu[0] = 0;
  q.push(0);
  for(int i = 1;i <= k;i++)
    spread(i);
  
  cout << solve(k - m) << endl;
  return 0;
}
