
// https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

// Common file containing the tree-based data structure we will use which is present in this file
#include <ext/pb_ds/assoc_container.hpp>
// Including tree_order_statistics_node_update
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using namespace 	__gnu_pbds;

struct Cmp
{
    bool operator ()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.first < b.first;
    }
};

#define oset tree<pair<int , int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>

oset s;
int n , q;
int ar[200000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;

	for (int i = 0; i < n; i++) {	
		cin >> ar[i];
		s.insert({ar[i], i});
	}

	for (int i = 0 ; i < q ; i++) {
		char c;
		cin >> c;
		if (c == '!') {
			int pos, value;
			cin >> pos >> value; 
			pos--;
			s.erase({ar[pos], pos});
			ar[pos] = value;
			s.insert({value, pos});
		}
		else {
			int a ,b ;
			cin >> a >> b;
			cout << s.order_of_key({b+1, 0}) - s.order_of_key({a, 0}) << "\n";
		}
	}
}
