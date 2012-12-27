#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
#define INF (1<<29)
typedef pair<int, int> P;

vector<P> edge[105000];
P edgeplace[105000], edges[105000];
int nice_node[105000], depth[105000];
int up[1 << 19], down[1 << 19], dseg[1 << 19];

void setnum(int* seg, int pos, int x){
    seg[pos += (1 << 18)] = x;
    while(pos /= 2){
	int l = pos * 2, r = pos * 2 + 1;
	seg[pos] = seg[l] + seg[r];
    }
}

int getsum(int *seg, int l, int r, int bottom = 0, int top = (1 << 18) - 1, int num = 1){
    if(r < bottom || top < l)return 0;
    if(l <= bottom && top <= r){
	return seg[num];
    }
    else{
	int mid = (bottom + top) / 2;
	return getsum(seg, l, r, bottom, mid, num * 2) + getsum(seg, l, r, mid + 1, top, num * 2 + 1);
    }
}

void setdepth(int* seg, int pos, int x){
    seg[pos += (1 << 18)] = x;
    while(pos /= 2){
	int l = pos * 2, r = pos * 2 + 1;
	if(depth[seg[l]] < depth[seg[r]]){
	    seg[pos] = seg[l];
	}
	else{
	    seg[pos] = seg[r];
	}
    }
}

int getmin(int *seg, int l, int r, int bottom = 0, int top = (1 << 18) - 1, int num = 1){
    if(r < bottom || top < l)return 0;
    if(l <= bottom && top <= r){
	return seg[num];
    }
    else{
	int mid = (bottom + top) / 2;
	int ll = getmin(seg, l, r, bottom, mid, num * 2);
	int rr = getmin(seg, l, r, mid + 1, top, num * 2 + 1);
	if(depth[ll] < depth[rr])
	    return ll;
	else
	    return rr;
    }
}



int make_tree(int x, int last = -1, int n = 1, int d = 1){
    depth[x] = d;
    setdepth(dseg, n, x);
    nice_node[x] = n;
    for(int i = 0;i < edge[x].size();i++){
	int to = edge[x][i].first, e = edge[x][i].second;
	if(to == last)continue;
	if(edges[e].first == to)swap(edges[e].first, edges[e].second);
	edgeplace[e].first = n;
	setnum(up, n, 1);
	setnum(down, n, 1);
	n = make_tree(to, x, n + 1, d + 1);
	edgeplace[e].second = n;
	setnum(up, n, -1);
	setnum(down, n, -1);
	setdepth(dseg, n, x);
	n++;
    }
    return n;
}



void update(int e, int s, int t){
    int plus = edgeplace[e].first, minus = edgeplace[e].second;
    int from = edges[e].first, to = edges[e].second;
    if(from < to){
	setnum(down, plus, s);
	setnum(up, plus, t);
	setnum(down, minus, -s);
	setnum(up, minus, -t);
    }
    else{
	setnum(up, plus, s);
	setnum(down, plus, t);
	setnum(up, minus, -s);
	setnum(down, minus, -t);
    }
}

int lca(int x, int y){
    int nx = nice_node[x], ny = nice_node[y];
    if(nx > ny)swap(nx, ny);
    return getmin(dseg, nx, ny);
}

int dist(int* seg, int r, int n){
    int nr = nice_node[r], nn = nice_node[n];
    return getsum(seg, nr, nn - 1);
}


int main(){
    int n, m, p, q, r, s, t, x, y, a;
    char query;
    cin >> n >> m;
    for(int i = 0;i < n-1;i++){
	cin >> p >> q;
	edge[p].push_back(P(q, i));
	edge[q].push_back(P(p, i));
	edges[i] = P(p, q);
    }
    depth[0] = INF;
    make_tree(1);
    for(int i = 0;i < m;i++){
	scanf(" %c", &query);
	if(query == 'I'){
	    scanf("%d %d %d", &r, &s, &t);
	    update(r-1, s, t);
	}
	else{
	    scanf("%d %d", &x, &y);
	    a = lca(x, y);
	    cout << dist(up, a, x) + dist(down, a, y) << endl;
	}
    }
    return 0;
}
