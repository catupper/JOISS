#include<iostream>
#include<algorithm>

using namespace std;

int n, m, t, x, y, tk, nk, mk, p[11], score[1050], w[1050][11], s[1050][11];
string cond;

int main(){
    cin >> n >> m >> t >> x >> y;
    for(int i = 1;i <= m;i++)	
	cin >> p[i];
  
    for(int i = 0;i < y;i++){
	cin >> tk >> nk >> mk >> cond;
	if(cond == "open"){
	    s[nk][mk] = tk;
	}
	if(cond == "incorrect"){
	    w[nk][mk]++;
	}
	if(cond == "correct"){
	    if(tk > t)continue;
	    score[nk] += max(x, p[mk] - (tk - s[nk][mk]) - 120 * w[nk][mk]);
	}
    }
    for(int i = 1;i <= n;i++)
	cout << score[i] << endl;
    return 0;
}
