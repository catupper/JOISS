#include<iostream>
#include<algorithm>
using namespace std;
int k, n, m, point[105000], now[105000];

int main(){
    cin >> k >> n >> m;
    n -= m;
    for(int i = 0;i < k;i++){
	cin >> point[i];
	now[i] = point[i];
    }
    sort(now, now + k);
    int g = k - (((k - 1) / 12) + 1);
    while(g > 0 && now[g] == now[g - 1])g--;
    for(int i = 0;i < k && g != 0;i++){
	if(point[i] >= now[g - 1] + n * 100)
	    cout << i + 1 << endl;
    }
    cout << "--------" << endl;
    for(int i = 0;i < k;i++){
	if(point[i] + n * 100 >= now[g])
	    cout << i + 1 << endl;
    }
    return 0;
}/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 20 22 23

12 11
13 11
23 21
24 22
 */
