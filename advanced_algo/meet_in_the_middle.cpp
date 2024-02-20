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
ll ans = 0;
vector<int>subset;
int n, x;

void solve(){
	scanf("%d%d", &n, &x);
	if (n == 1) {
		int temp;
		scanf("%d", &temp);
		if (temp == x) cout << 1;
		else cout << 0;
		return;
	}
	vector<ll>a(n/2);
	vector<ll>b(n - n/2);
	for (int i = 0 ; i < n / 2; i++){
		scanf("%d", &a[i]);
	}
	for (int i = n/2; i < n ; i++){
		scanf("%d", &b[i - n/2]);
	}
	vector<ll>sum_A;
	sum_A.push_back(0);
	for (int i = 0 ; i < (1<<a.size()); i++){
		ll sum = 0;
		for (int j = 0 ; j < a.size(); j++){
			if (i & (1 << j)) sum += a[j];
		}
		if (sum > 0) sum_A.push_back(sum);
	}
	sort(sum_A.begin(), sum_A.end());
	vector<ll>sum_B;
	sum_B.push_back(0);
	for (int i = 0 ; i < (1<<b.size()); i++){
		ll sum = 0;
		for (int j = 0 ; j < b.size(); j++){
			if (i & (1 << j)) sum += b[j];
		}
		if (sum > 0) sum_B.push_back(sum);
	}
	sort(sum_B.begin(), sum_B.end());
	for (int i = 0 ; i < sum_A.size(); i++){
		ans += upper_bound(sum_B.begin(), sum_B.end(), x - sum_A[i]) - lower_bound(sum_B.begin(), sum_B.end(), x-sum_A[i]);
	}
	printf("%lld\n", ans);
}

int main(){
	solve();
}


