#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int loop[105000], nice_n[105000], last[105000], bit[105000], n, parent[105000];
vector<int> child[105000];
bool come[105000];

int comp(int x){
    if(come[x])return x;
    if(loop[x] != 0)return -1;
    int res = -1;
    come[x] = true;
    for(int i = 0;i < child[x].size();i++){
	int t = comp(child[x][i]);
	if(t != -1)res = t;
    }
    if(res == -1 || res == x)loop[x] = x;
    else{
	loop[x] = res;
	for(int i = 0;i < child[x].size();i++){
	    child[res].push_back(child[x][i]);
	}
    }
    come[x] = false;
    if(x == res)return -1;
    else return res;
}

int nice_node(int x, int n = 0){
    x = loop[x];
    if(nice_n[x] != 0)return n;
    n++;
    nice_n[x] = n;
    cout << n << endl;
    for(int i = 0;i < child[x].size();i++){
	n = nice_node(child[x][i], n);
    }
    last[x] = n;
    return n;
}

int sum(int x){
    int res = 0;
    while(x){
	res += bit[x];
	x -= x & -x;
    }
    return res;
}

int solve(int x){
    if(nice_n[x] <= 0){cout << last[x] << endl;exit(0);}
    return sum(last[x]) - sum(nice_n[x] - 1);
}

void report(int x){
    x = nice_n[x];
    while(x < 105000){
	bit[x]++;
	x += x & -x;
    }
}

int main(){
    cin >> n;
    for(int i = 1;i <= n;i++){
	cin >> parent[i];
	child[parent[i]].push_back(i);
    }
    for(int i = 1;i <= n;i++){
	fill(come, come + 105000, false);
	if(loop[i] == 0)comp(i);
    }
    int p = 0;
    for(int i = 1;i <= n;i++){
	if(nice_n[loop[i]] == 0){
	    while(loop[i] == i)i = parent[i];	    
	    p = nice_node(loop[i], p);
	}
    }
    for(int i = 1;i <= n;i++){
	/*cout <<*/ solve(loop[i]) /*<< endl*/;
	report(loop[i]);
    }
}
/*

2 4 6

  3

 1 5

 */
