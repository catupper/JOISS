#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

int main(){
    map<int, int> typhoon;
    cin >> n >> m >> k;
    for(int i = 0;i < n;i++){
	cin >> a >> b;
	if(typhoon.find(a) == typhoon.end())typhoon[a] = 0;
	if(typhoon.find(b) == typhoon.end())typhoon[b] = 0;
	typhoon[a]++;
	typhoon[b]--;
    }
    for(int i = 0;i < m;i++){
	cin >> p >> q >> r;
    
    }
}
