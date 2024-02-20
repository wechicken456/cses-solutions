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
#define sort_all(a) sort(a.begin(), a.end())

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

const maxN = 2e5;
int n, m;
int h[maxN];
void solve(){
	cin >> n >> m;
	for (int i = 0; i  < n; i++){
		cin >> h[i];
	}
	vector<pair<int,int>>t(m);
	for (int i = 0; i < m; i++) {
		cin >> t[i].first;
		t[i].second = i;
	}
	sort_all(t);
	sort_all(h);
	vector<int>ans(m);
	for (int i = 0 , j = 0; i < m; i++ ){
		while (j < n && h[j] <= t[i]) {
			j++;
		}
		
	}
}

int main(){
	solve();
}


