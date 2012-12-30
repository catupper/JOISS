#include<iostream>
#include<functional>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
#define INF (1 << 29)
typedef pair<int, int> P;
typedef pair<int, P> E;
int p[1050], cost[1050][1050], n, cnt[4], mincost[1050];
bool used[1050];

void allstar(){
    int res = 0, edge = 0;
    for(int i = 0;i < n;i++)
	for(int j = i + 1;j < n;j++)
	    if(p[i] == 1 || p[j] == 1){
		res += cost[i][j];
		edge++;
	    }
    cout << edge << ' ' << res << endl;
}

void onestar(){
    int res = 1 << 30, edge = n - 1;
    for(int i = 0;i < n;i++){
	int tmp = 0;
	for(int j = 0;j < n;j++)
	    tmp += cost[i][j];
	res = min(res, tmp);
    }
    cout << edge << ' ' << res << endl;
}

void twostar(){
    int t[2], pp = 0;
    for(int i = 0;i < n;i++)
	if(p[i] == 2)
	    t[pp++] = i;
	
    int res = cost[t[0]][t[1]], edge = n - 1;
    for(int i = 0;i < n;i++)
	if(p[i] != 2)
	    res += min(cost[i][t[0]], cost[i][t[1]]);
    
    cout << edge << ' ' << res << endl;
    
}

void krskl(){
    int res = 0, edge = n - 1;
    fill(mincost, mincost + 1050, INF);
    mincost[0] = 0;
    while(true){
	int v = -1;
	for(int i = 0;i < n;i++)
	    if(!used[i] && (v == -1 || mincost[i] < mincost[v]))v = i;
	if(v == -1)break;
	used[v] = true;
	res += mincost[v];
	for(int i = 0;i < n;i++)
	    mincost[i] = min(mincost[i], cost[i][v]);
    }
    cout << edge << ' ' << res << endl;    
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> p[i];
	cnt[p[i]]++;
    }
    for(int i = 0;i < n;i++)
	for(int j = 0;j < n;j++)
	    cin >> cost[i][j];
    if(cnt[1] != 0){
	allstar();
    }
    else if(cnt[2] > 2){
	onestar();
    }
    else if(cnt[2] == 2){
	twostar();
    }
    else{
	krskl();
    }
    return 0;
}
