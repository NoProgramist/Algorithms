#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <ctime>

#pragma comment(linker, "/STACK:36777216")
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define pii pair<int,int>
#define pdd pair<double,double>
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i >= _b; --i)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,0,(n)-1)
#define VI vector <int>
#define ll long long
#define sqr(x) ((x)*(x))

int ddx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int ddy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

using namespace std;

#define MOD 1000000007
#define R2 500000004
#define R3 333333336
#define INF 1000000000
#define EPS 1e-6
#define PI 3.1415926535897932384626433832795028841971
#define MAX 100010
using namespace std;


VI Zfunction(string s)
{
	VI z(s.size());
	int l = 0, r = 0;
	FOR(i,1,s.size()-1)
	{
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}


VI Pfunction(string s)
{
	VI pi(s.size());
	FOR(i, 1, s.size()-1)
	{
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}


int main()
{
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	VI P = Pfunction(s);
	VI Z = Zfunction(s);
	rep(i, s.size())
		cout << P[i] << ' ';
	cout << endl;
	rep(i, s.size())
		cout << Z[i] << ' ';
	cin >> s;
	return 0;
}
