#include<iostream>
#include<set>
using namespace std;

int main(){
	int n;
	cin >> n;
	long long x;
	set<long long>s;
	for (int i = 0 ; i < n; i++){
		cin >> x;
		s.insert(x);
	}
	cout << s.size() << "\n";
}
