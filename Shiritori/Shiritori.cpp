#include<iostream>
#include<iomanip>
#include<functional>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<long long, long long> P;

long long n, x;
int cnt[6], inout[105];
priority_queue<P, vector<P>, greater<P> > edge[105];

void solve(int x){
    while(!edge[x].empty()){
	P tmp = edge[x].top();edge[x].pop();
	cout << setw(10) << setfill('0') << right << tmp.first << endl;
	x = tmp.second;
    }
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> x;
	int from = x / 100000000, to = x % 100;
	edge[from].push(P(x, to));
	inout[from]++;
	inout[to]--;
    }
    int start = -1;
    for(int i = 0;i < 100;i++){
	if(inout[i] < -1 || inout[i] > 1){
	    cout << "impossible" << endl;
	    return 0;
	}
	if(inout[i] == 1)start = i;
	cnt[inout[i] + 1]++;
    }
    if(cnt[0] > 1){
	cout << "impossible" << endl;
	return 0;
    }
    if(start == -1){
	start = 0;
	while(edge[start].empty())start++;
    }
    solve(start);
    return 0;
}


/*

0 - 1 = 3
    | /
    2
 */
