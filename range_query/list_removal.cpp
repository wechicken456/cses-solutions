#include<bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
	int n;
	cin >> n;
	vector<char>a(n+1);
	for (int i = 1 ; i <= n; i++){
		cin >> a[i];
	}
	int old_n = n;
	for (int i = 1; i <= old_n; i++){
		int pos;
		cin >> pos;
		cout << a[pos] << " ";
		auto it = a.begin() + pos;
		a.erase(it);
		n--;
	}
}
