#include<iostream>
#include<algorithm>

using namespace std;

long long res;
int h, w, f[420][420];

long long solve(int x, int y){
    long long res = 0, p[1 << 3];
    fill(p, p + (1 << 3), 0);
    for(int i = 0;i < w;i++)
	p[(1 << f[x][i]) | (1 << f[y][i])]++;
    
    for(int i = 1;i < (1 << 3);i++)
	for(int j = i + 1;j < (1 << 3);j++)
	    if((i | j) == 7)
		res += p[i] * p[j];
	    
    return res;
}

int main(){
    cin >> h >> w;
    for(int i = 0;i < h;i++)
	for(int j = 0;j < w;j++)
	    cin >> f[i][j];
    
    for(int i = 0;i < h;i++)
	for(int j = i + 1;j < h;j++)
	    res += solve(i, j);
    
    cout << res << endl;
}
