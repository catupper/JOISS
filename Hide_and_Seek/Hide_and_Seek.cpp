#include<iostream>
#include<cstring>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> P;
typedef pair<P, int> WALL;

struct segnode{
    segnode(){
	all = 0;
	maximum = 0;
    }
    int all, maximum;
};

vector<WALL> wall;
int ans[50000][2];
segnode seg[1 << 18];

void add_seg(int pos, int bottom, int top, int left, int right){
    if(right < bottom || top < left)
	return;

    if(left <= bottom && top <= right)
	seg[pos].all++;
  
    else{
	int l = pos * 2, r = pos * 2 + 1, mid = (bottom + top) / 2;
	add_seg(l, bottom, mid, left, right);
	add_seg(r, mid + 1, top, left, right);
	seg[pos].maximum = max(seg[l].maximum + seg[l].all, seg[r].maximum + seg[r].all);
    }
}

int maxvalue(){
    return seg[1].maximum + seg[1].all;
}

int minx(int pos, int left, int right){
    if(left == right)return left;
    int l = pos * 2 , r = pos * 2 + 1, mid = (left + right) / 2;
    if(seg[l].maximum + seg[l].all == seg[pos].maximum)
	return minx(l, left, mid);
    else
	return minx(r, mid + 1, right);
}

void solve(){
    vector<WALL>::iterator it = wall.begin();
    while(it != wall.end()){
	int x = (*it).first.second, y = (*it).first.first, w = (*it).second;
	it++;
	add_seg(1, 0, 1 << 16, x, x + w - 1);
	int m = maxvalue();
	if(ans[m][0] != -1)continue;
	ans[m][0] = minx(1, 0, 1 << 16);
	ans[m][1] = y;
    }
}

int main(){
    int n, m, w, x, y, q;
    memset(ans, -1, sizeof(ans));
    cin >> n >> m;
    for(int i = 0;i < n;i++){
	cin >> x >> y >> w;
	wall.push_back(WALL(P(y, x), w));
    }
    sort(wall.begin(), wall.end());
    solve();
    for(int i = 0;i < m;i++){
	cin >> q;
	q++;
	cout << ans[q][0] << ' ' << ans[q][1] << endl;
    }
    return 0;
}
