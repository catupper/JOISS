#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int fail[3150][3150], plug[3150], alt[3150], altsum[3150];
vector<int> v;

bool comp(const int & x, const int & b){
    return alt[x] < alt[b];
}

void solve(){
    for(int i = 0;i < v.size();i++){
	int tmp = v[i];
	plug[tmp] = altsum[tmp];
	for(int j = 0;j < v.size();j++){
	    if(fail[v[j]][plug[tmp]] == 0){
		altsum[v[j]] -= plug[tmp];
	    }
	}
    }
}



int main(){
    int n, m, a, b, c, d;
    cin >> n >> m;
    for(int i = 0;i < m;i++){
	cin >> a >> b >> c >> d;
	b++,d++;
	fail[a][c]++;
	fail[a][d]--;
	fail[b][c]--;
	fail[b][d]++;
    }
    for(int i = 0;i < 3150;i++)
	for(int j = 1;j < 3150;j++)
	    fail[i][j] += fail[i][j - 1];
    for(int i = 1;i < 3150;i++)
	for(int j = 0;j < 3150;j++)
	    fail[i][j] += fail[i - 1][j];

    for(int i = 1;i <= n;i++)
	for(int j = 1;j <= n;j++)
	    if(fail[i][j] == 0){
		alt[i]++;
		altsum[i] += j;
	    }

    for(int i = 1;i <= n;i++)
	v.push_back(i);
    sort(v.begin(), v.end(), comp);
    solve();

    for(int i = 1;i <= n;i++)
	cout << plug[i] << endl;
    return 0;
}


