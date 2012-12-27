#include<iostream>
#include<string>
using namespace std;


string solve(int n, int k){
    if(n == 0)return "J";
    string res;
    if(k <= 1 << (n - 1)){
	for(int i = 0;i < 1 << (n - 1);i++){
	    res += "J";
	}
	for(int i = 0;i < 1 << (n - 1);i++){
	    res += "O";
	}
    }
    else{
	for(int i = 0;i < 1 << (n - 1);i++){
	    res += "I";
	}    
	res += solve(n - 1,k - (1 << (n - 1)));
    }
    return res;
}


int main(){
    int n, k;
    cin >> n >> k ;
    cout << solve(n, k) << endl;
}
