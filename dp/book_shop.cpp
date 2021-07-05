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
int n,x;
void solve(){
	scanf("%d%d", &n, &x);
	vector<vector<int>>max_book(n+1, vector<int>(x+1, 0));
	vector<int>price(n+1);
	vector<int>pages(n+1);
	for (int i = 1;  i <= n; i++){
		scanf("%d", &price[i]);
	}
	for (int i = 1; i <= n;i ++){
		scanf("%d", &pages[i]);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 0 ; j <= x; j++){
			max_book[i][j] = max_book[i-1][j];				// best so far if we don't buy the current i-th book.
			int money_left = j - price[i];
			if (money_left >= 0){							// if not enough money for i-th book, best so far is best of first i-1 th books.
				max_book[i][j] = max(max_book[i][j], max_book[i-1][money_left] + pages[i]);		// compare not buy vs buy i-th book.
			}
		}
	}
	printf("%d", max_book[n][x]);
}

int main(){
	solve();
}


