#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
#define INF (1 << 30)
typedef pair<int, int> P;
int top[1050], pot[1050], parent[1050], imos[1050], dp[1050][1050], checkpoint[1050], a, b, c, n, m;
vector<P> edge[1050];

int topo(int x, int t = 1){
    if(--parent[x] > 0)return t;
    pot[x] = t;
    top[t++] = x;
    for(int i = 0;i < edge[x].size();i++){
	t = topo(edge[x][i].first, t);
    }
    return t;
}

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
	cin >> checkpoint[i];
    }
    for(int i = 0;i < m;i++){
	cin >> a >> b >> c;
	edge[a].push_back(P(b, c));
	parent[b]++;
    }
    topo(1);
    for(int i = 1;i <= n;i++){
	imos[i] = imos[i - 1] + checkpoint[top[i]];
    }

    for(int i = 1;i <= n;i++)
	for(int j = 1;j <= n;j++)
	    dp[i][j] = INF;

    dp[1][1] = 0;
    for(int i = 1;i <= n;i++){
	for(int j = i;j <= n;j++){
	    vector<P>::iterator it = edge[top[i]].begin();
	    while(it != edge[top[i]].end()){
		int to = (*it).first, pt = pot[to], d = (*it).second;
		if(imos[pt] <= imos[j] || imos[j] + 1 == imos[pt] && checkpoint[to]){
		    if(j <= pt)
			dp[j][pt] = min(dp[j][pt], dp[i][j] + d);
		    else
			dp[pt][j] = min(dp[pt][j], dp[i][j] + d);
		}
		it++;
	    }
	    it = edge[top[j]].begin();
	    while(it != edge[top[j]].end()){
		int to = (*it).first, pt = pot[to], d = (*it).second;
		if(imos[pt] == imos[j] || imos[pt] == imos[j] + 1 && checkpoint[to]){
		    dp[i][pt] = min(dp[i][pt], dp[i][j] + d);
		}
		it++;
	    }
	}
    }
    cout << dp[n][n] << endl;
}
