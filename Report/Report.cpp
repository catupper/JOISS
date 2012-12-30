#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> child[105000];
int parent[105000], loop[105000], bit[105000], last[105000], nice_n[105000], n;
bool come[105000];

int comp(int x){
    if(come[x])return x;
    if(loop[x] != 0)return -1;
    int res = -1;
    come[x] = true;
    for(int i = 0;i < child[x].size();i++){
	int tmp = comp(child[x][i]);
	if(tmp != -1)res = tmp;
    }
    loop[x] = x;
    if(res == x)return -1;
    if(res != -1){
	loop[x] = res;
	for(int i = 0;i < child[x].size();i++){
	    child[res].push_back(child[x][i]);
	}
    }
    come[x] = false;
    return res;
}

int nice_node(int x, int p){
    x = loop[x];
    if(nice_n[x] != 0)return p;
    p++;
    nice_n[x] = p;
    for(int i = 0;i < child[x].size();i++){
	p = nice_node(child[x][i], p);
    }
    last[x] = p;
    return p;
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
    return sum(last[x]) - sum(nice_n[x] - 1);
}

void report(int x){
    x = nice_n[x];
    while(x <= 105000){
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

    for(int i = 1;i <= n;i++)
	comp(i);   

    int p = 0;
    for(int i = 1;i <= n;i++){
	int j = i;
	if(nice_n[loop[j]] == 0){
	    while(loop[j] == j)j = parent[j];	    
	    p = nice_node(j, p);
	}
    }

    for(int i = 1;i <= n;i++){
	cout << solve(loop[i]) << endl;
	report(loop[i]);
    }
}
