#include<iostream>
#include<map>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;

typedef pair<vector<int>*, vector<int>* > PV;

int h[105000], res, n, a, b, p;
vector<int> edge[105000];
vector<int> v[525000];
void make_edge(int x, int y){
    edge[x].push_back(y);
    edge[y].push_back(x);
}

int solve(vector<int> *down, vector<int> *up, int x){
    int res;
    res = (int)(lower_bound(down->begin(), down->end(), x) - down->begin())+ (int)(lower_bound(up->begin(), up->end(), x, greater<int>()) - up->begin()) + 1;
    if(down->size() > up->size()){
	res = max(res, (int)down->size());
	for(int i = 0;i < up->size();i++){
	    int tmp = lower_bound(down->begin(), down->end(), up->at(i)) - down->begin();
	    res = max(res, i + tmp + 1);
	}
    }
    else{
	res = max(res, (int)up->size());
	for(int i = 0;i < down->size();i++){
	    int tmp = lower_bound(up->begin(), up->end(), down->at(i), greater<int>()) - up->begin();
	    res = max(res, i + tmp + 1);
	}
    }
    return res;
}

vector<int> *merged(vector<int> *a, vector<int> *b){
    int minsize = min(a->size(), b->size());
    for(int i = 0;i < minsize;i++){
	a->at(i) = b->at(i) = max(a->at(i), b->at(i));
    }
    if(a->size() > b->size())return a;
    else return b;
}

vector<int> *mergeu(vector<int> *a, vector<int> *b){
    int minsize = min(a->size(), b->size());
    for(int i = 0;i < minsize;i++){
	a->at(i) = b->at(i) = max(a->at(i), b->at(i));
    }
    if(a->size() > b->size())return a;
    else return b;
}

PV dfs(int x, int last = -1){
    vector<int> *down = v + p++, *up = v + p++, *td = v + p++, *tu = v + p++;
    vector<int>::iterator it;

    for(int i = 0;i < edge[x].size();i++){
	if(edge[x][i] == last)continue;
	PV tmp = dfs(edge[x][i], x);
	td = tmp.first;
	tu = tmp.second;
	res = max(res, solve(down, tu, h[x]));
	res = max(res, solve(td, up, h[x]));
	up = mergeu(up, tu);
	down = merged(down, td);
    }
    it = lower_bound(down->begin(), down->end(), h[x]);
    if(it == down->end())down->push_back(h[x]);
    else *it = h[x];
    it = lower_bound(up->begin(), up->end(), h[x], greater<int>()) ;
    if(it == up->end())up->push_back(h[x]);
    else *it = h[x];
    res = max(res, (int)down->size());
    res = max(res, (int)up->size());
    return PV(down, up);
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> h[i];
    }
    for(int i = 0;i < n - 1;i++){
	cin >> a >> b;
	a--,b--;
	make_edge(a, b);
    }

    dfs(0);

    cout << res << endl;
    return 0;
}
/*


4 
2
5 3 1
8
7
*/
