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
#define MAX 200
using namespace std;


int g[MAX][MAX];
int w[MAX];
VI cut;
bool destroyed[MAX];
bool added[MAX];
VI v[MAX];

int main()
{
	int n;
	cin >> n;
	rep(i, n)
		rep(j, n)
			cin >> g[i][j];
	int cost = INF;
	rep(i, n)
		v[i].push_back(i);
	rep(i, n - 1)
	{
		memset(added, 0, n * sizeof added[0]);
		memset(w, 0, n * sizeof w[0]);
		int last;
		rep(j, n - i)
		{
			int best = -1;
			rep(v, n)
				if (!destroyed[v] && !added[v] && (best == -1 || w[v] > w[best]))
					best = v;
			if (j == n - i - 1)
			{
				if (w[best] < cost)
					cost = w[best],
					cut = v[best];				
				rep(k, v[best].size())
					v[last].push_back(v[best][k]);
				destroyed[best] = 1;
				rep(k, n)
					g[last][k] = g[k][last] += g[best][k];
			}
			else
			{
				added[best] = 1;
				rep(k, n)
					w[k] += g[best][k];
				last = best;
			}
		}
	}
	cout << cost << endl;
	rep(i, cut.size())
		cout << cut[i] << ' ';
	cin >> n;
	return 0;
}
