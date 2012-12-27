#include<iostream>
#include<algorithm>
using namespace std;

int main(){
  int x[] = {1,2,3,4,5,6,7,8,9};
  cout << upper_bound(x, x + 9,8) - x << endl;
}
