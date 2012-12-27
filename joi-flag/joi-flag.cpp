#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define INF (1 << 29)
typedef pair<int, int> P;
typedef pair<P, char> qu;

map<pair<pair<int, int>, pair<int, int> >, int> table;
vector<qu> joi;
int k, n, x, y;
char c;

int countnot(char c, vector<qu> joi){
    int res = 0;
    for(int i = 0;i < joi.size();i++){
	if(joi[i].second != c)res++;
    }
    return res;
}

int solve(int k, int x1, int x2, int y1, int y2, vector<qu> joi, char x){
    if(table.find(make_pair(make_pair(x1, y1), make_pair(k, x))) != table.end())
	return table[make_pair(make_pair(x1, y1), make_pair(k, x))];
    if(joi.empty() || k == 1 && x == 'S')return table[make_pair(make_pair(x1, y1), make_pair(k, x))] = 0;

    if(x != 'S')
	return table[make_pair(make_pair(x1, y1), make_pair(k, x))] = countnot(x, joi);
  
    k >>= 1;

    int ans = INF;
    vector<qu> tmp0, tmp1, tmp2, tmp3;
    for(int i = 0;i < joi.size();i++){
	if(x1 <= joi[i].first.first && joi[i].first.first < x2 - k && y1 <= joi[i].first.second && joi[i].first.second < y2 - k)
	    tmp0.push_back(joi[i]);
	else if(x1 <= joi[i].first.first && joi[i].first.first < x2 - k && y1 + k <= joi[i].first.second && joi[i].first.second < y2)
	    tmp1.push_back(joi[i]);
	else if(x1 + k <= joi[i].first.first && joi[i].first.first < x2 && y1 <= joi[i].first.second && joi[i].first.second < y2 - k)
	    tmp2.push_back(joi[i]);
	else if(x1 + k <= joi[i].first.first && joi[i].first.first < x2 && y1 + k <= joi[i].first.second && joi[i].first.second < y2)
	    tmp3.push_back(joi[i]);
    }


    char sets[] = {'I', 'J', 'O', 'S'};
    int p = 0;
    do{
	int r = 0;
	r += solve(k, x1, x2 - k, y1, y2 - k, tmp0, sets[0]);
	r += solve(k, x1, x2 - k, y1 + k, y2, tmp1, sets[1]);
	r += solve(k, x1 + k, x2, y1, y2 - k, tmp2, sets[2]);
	r += solve(k, x1 + k, x2, y1 + k, y2, tmp3, sets[3]);
	ans = min(ans, r);
    }while(next_permutation(sets, sets + 4));
    return table[make_pair(make_pair(x1, y1), make_pair(k, x))] = ans;
}

int main(){
    vector<pair<P, char> > joi;
    cin >> k >> n;
    for(int i = 0;i < n;i++){
	cin >> x >> y >> c;
	x--,y--;
	joi.push_back(qu(P(x, y), c));
    }
    cout << solve(1 << k, 0, 1 << k, 0, 1 << k, joi, 'S') << endl;
    return 0;
}
