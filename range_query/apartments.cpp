#include<vector>
#include<iostream>
#include<algorithm>

typedef long long ll;
using namespace std;

int main(){
	int n,m;
	ll k;
	cin >> n >> m >> k;
	vector<ll>cus = vector<ll>(n);
	vector<ll>aparts = vector<ll>(m);
	for (int i = 0; i < n ; i++){
		cin >> cus[i];
	}
	for (int i = 0 ; i < m; i++){
		cin >> aparts[i];
	}
	ll ans = 0 ;
	sort(cus.begin(), cus.end());
	sort(aparts.begin(), aparts.end());
	ll cur = 0;
	for (int i = 0;  i < n; i++){
		while (cur < m && aparts[cur] < cus[i]-k){
			cur++;
		}
		if (cur < m && aparts[cur] <= cus[i]+ k ) {
			ans++; 
			cur++;
		}
	}
	cout << ans << "\n";
}
