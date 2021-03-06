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

const int maxN = 1e5;
const int maxX = 1000;
int n, m,x;

void solve(){
	cin >> n;
	vector<int>a;
	for (int i = 0, x; i < n; i++){
		cin >> x;
		auto it = lower_bound(a.begin(), a.end(), x);
		if (it != a.end()) *it = x;
		else a.pb(x);
		
	}	
	cout << a.size() << "\n";
}

int main(){
	solve();
}


