#include<bits/stdc++.h>
#include<set>
#include<stdio.h>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<math.h>
#include<cmath>
#include<fstream>

#define ll long long
#define ull unsigned long long
#define pb push_back

using namespace std;

ull power(ll x, ull y) {
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    else
        return x * power(x, y / 2) * power(x, y / 2);
}
 
ll my_ceil(ll a, ll b) {
	return (a/b) + ( (a%b)!=0 );
}

const int maxN = 500;
const int maxX = 1000;
int n, m,x;
int series[maxN + 1];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		series[i] = i + series[i-1];
		cout << series[i] << " " ;
	}
	if (series[n] % 2 == 1) cout << 0;
	else {
		
	}
}

int main(){
	solve();
}


