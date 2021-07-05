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

void solve(){
	int ans = 0 ; 
	int n , x;
	scanf("%d%d", &n, &x);
	vector<int>child(n);
	for (int i = 0 ; i < n;i ++){
		scanf("%d", &child[i]);
	}
	sort_all(child);
	int j = n - 1;
	for (int i = 0 ; i < j; i++){
		for (; j >= i && child[i] + child[j] > x; j--);
		if (i >= j) break;
		ans++;
		j--;
	}
	printf("%d", n - ans);
}

int main(){
	solve();
}


