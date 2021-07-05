#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long

using namespace std;

void solve(){
	int n, x;
	cin >> n >> x;
	vector<int>num(n);
	for (int i = 0 ; i < n; i++){
		cin >> num[i];
	}
	ll ans = 0;
	cout << (1 << 20) << "\n";
	for (ull i=0; i< (1<<n); i++){
        ll sum = 0;
        for (int j=0; j<n; j++) {
            if (i & (1<<j)) sum += num[j];
		}
       	if (sum == x) ans++;
    }
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}
