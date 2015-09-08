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

int p[MAX];
int sz[MAX];
int h[MAX];
VI g[MAX];

void dfs(int v, int pr = -1, int he = 1)
{
	p[v] = pr;
	sz[v] = 1;
	h[v] = he;
	rep(i, g[v].size())
		if (g[v][i] != pr)
			dfs(g[v][i], v, he + 1),
			sz[v] += sz[g[v][i]];
}

int CHAIN[MAX];
int HEAD[MAX];
int POS[MAX];
int CUR, DONE, n;
int t[MAX << 2];
int a[MAX];

void HLD(int v)
{
	if (HEAD[CUR] == -1)
		HEAD[CUR] = v;
	CHAIN[v] = CUR;
	POS[v] = DONE++;
	int mx = -1;
	rep(i, g[v].size())
		if (g[v][i] != p[v] && (mx == -1 || sz[i] > sz[mx]))
			mx = i;
	if (mx != -1)HLD(g[v][mx]);
	rep(i, g[v].size())
		if (g[v][i] != p[v] && i != mx)
			++CUR, HLD(g[v][i]);
}

void update(int v, int tl, int tr, int pos, int val)
{
	if (tl == tr) a[pos] = t[v] = val;
	else
	{
		int tm = tl + tr >> 1;
		if (pos <= tm) update(v + v, tl, tm, pos, val);
		else update(v + v + 1, tm + 1, tr, pos, val);
		t[v] = min(t[v + v], t[v + v + 1]);
	}
}

int GetMin(int v, int tl, int tr, int l, int r)
{
	if (l > r)return INF;
	if (l == tl && r == tr)return t[v];
	int tm = tl + tr >> 1;
	return min(GetMin(v + v, tl, tm, l, min(r, tm)), GetMin(v + v + 1, tm + 1, tr, max(l, tm + 1), r));
}

int GET(int u, int v)
{
	int ans = INF;
	for (;;)
	{	
		if (CHAIN[u] == CHAIN[v])
			return (ans = min(ans, GetMin(1, 0, n-1, min(POS[u], POS[v]), max(POS[u], POS[v])))) == INF ? -2 : ans;
		if (h[HEAD[CHAIN[u]]] < h[HEAD[CHAIN[v]]])swap(u, v);
		ans = min(ans, GetMin(1, 0, n - 1, POS[HEAD[CHAIN[u]]], POS[u]));
		u = p[HEAD[CHAIN[u]]];
	}
}


int main()
{
	int m;
	scanf("%d%d", &n, &m);
	rep(i, n - 1)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		--x, --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	memset(HEAD, -1, n * sizeof HEAD[0]);
	dfs(0);
	HLD(0);
	rep(i, n)
		update(1, 0, n - 1, POS[i], INF);
	rep(i, m)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (x)
			printf("%d\n", GET(y-1, 0)+1);
		else update(1, 0, n-1, POS[y-1], a[POS[y-1]] == INF ? y-1 : INF);
	}
	return 0;
}
