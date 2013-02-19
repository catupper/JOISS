#include<iostream>
#include<map>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;
typedef pair<long long, long long> P;
typedef pair<long long, P> T;

struct segnode{
    segnode(){
	val = 0;
	sum = 0;
    }
    long long val, sum;
};

segnode seg[1 << 19];
vector<P> fish;
vector<T> maxima;
long long n, fish_size, res;
char fish_color;
void add(long long left, long long right, long long val, long long pos = 1, long long bottom = 0, long long top = 1 << 18){
    if(right <= bottom || top <= left)return;
    if(seg[pos].val >= val)return;
    if(left <= bottom && top <= right){
	seg[pos].val = val;
	seg[pos].sum = seg[pos].val * (top - bottom);
    }
    else{
	long long mid = (bottom + top) / 2;
	if(seg[pos].val != 0){
	    seg[pos * 2].val = seg[pos].val;
	    seg[pos * 2].sum = seg[pos * 2].val * (mid - bottom);
	    seg[pos * 2 + 1].val = seg[pos].val;
	    seg[pos * 2 + 1].sum = seg[pos * 2 + 1].val * (top - mid);
	}
	seg[pos].val = 0;
	add(left, right, val, pos * 2, bottom, mid);
	add(left, right, val, pos * 2 + 1, mid, top);
	seg[pos].sum = seg[pos * 2].sum + seg[pos * 2 + 1].sum;
    }
}

long long sum(){
    return seg[1].sum;
}

int main(){
    cin >> n;
    for(long long i = 0;i < n;i++){
	cin >> fish_size >> fish_color;
	fish.push_back(P(fish_size, fish_color));
    }
    sort(fish.begin(), fish.end());
    long long r = 0, red = 0, green = 0, blue = 0;
    for(long long l = 0;l < n;l++){
	while(r < n && fish[r].first < fish[l].first * 2){
	    if(fish[r].second == 'R')red++;
	    if(fish[r].second == 'G')green++;
	    if(fish[r].second == 'B')blue++;
	    r++;
	}
	maxima.push_back(T(red + 1, P(green + 1, blue + 1)));
	if(fish[l].second == 'R')red--;
	if(fish[l].second == 'G')green--;
	if(fish[l].second == 'B')blue--;
    }
    maxima.push_back(T(0, P(0, 0)));
    sort(maxima.begin(), maxima.end(), greater<T>());
    add(0, maxima[0].second.first, maxima[0].second.second);
    for(long long i = 1;i < maxima.size();i++){

	res += (maxima[i - 1].first - maxima[i].first) * sum();
	add(0, maxima[i].second.first, maxima[i].second.second);
    }
    
    cout << res - 1 << endl;
    return 0;
}
