#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int p[4200][2], dp[4200][4200], dest[4200], n, res;
vector<int> points;
int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> p[i][0] >> p[i][1];
	points.push_back(p[i][0]);
	points.push_back(p[i][1]);
    }
    sort(points.begin(), points.end());
    vector<int>::iterator it = unique(points.begin(), points.end());
    points.erase(it, points.end());
    fill(dest, dest + 4200, -1);
    for(int i = 0;i < n;i++){
	p[i][0] = lower_bound(points.begin(), points.end(), p[i][0]) - points.begin();
	p[i][1] = lower_bound(points.begin(), points.end(), p[i][1]) - points.begin();
	if(p[i][0] < p[i][1])swap(p[i][0], p[i][1]);
	dest[p[i][0]] = p[i][1];
    }
    for(int i = 1;i < 4200;i++){
	for(int l = 0;l + i < 4200;l++){
	    int r = l + i;
	    dp[l][r] = dp[l][r - 1];
	    if(dest[r - 1] >= l){
		dp[l][r] = max(dp[l][r], dp[l][dest[r - 1]] + dp[dest[r - 1]][r - 1] + 1);
	    }
	    res = max(res, dp[l][r]);
	}
    }
    cout << res << endl;
}
