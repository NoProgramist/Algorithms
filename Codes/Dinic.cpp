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
#define MAX 20010
using namespace std;

int f[MAX];
int c[MAX];
int t[MAX];
int d[111];
int q[MAX];
int w[111];
VI g[111];
int cur,n,m;

bool bfs()
{
	int l = 0, r = 0;
	memset(d, -1, (n+1) * sizeof d[0]);
	q[r++] = 1;
	d[1] = 0;
	while (l < r && d[n] == -1)
	{
		int v = q[l++];
		rep(i, g[v].size())
			if (d[t[g[v][i]]] == -1 && f[g[v][i]] < c[g[v][i]])
				q[r++] = t[g[v][i]],
				d[t[g[v][i]]] = d[v] + 1;

	}
	return d[n] != -1;
}

int dfs(int v, int flow)
{
	if (!flow )return 0;
	if (v == n)return flow;
	for (; w[v] < g[v].size(); ++w[v]){
		int e = g[v][w[v]];
		if (d[t[e]] == d[v] + 1)
			if (int x = dfs(t[e], min(flow, c[e] - f[e]))){
				f[e] += x;
				f[e ^ 1] -= x;
				return x;
			}
	}
	return 0;
}

int dinic()
{
	int FLOW = 0;
	while(bfs()){
		memset(w, 0, (n + 1) * sizeof w[0]);
		while (int flow = dfs(1, INF))
			FLOW += flow;
	}
	return FLOW;
}


int main()
{
	cin >> n >> m;
	rep(i, m)
	{
		int u, v, cc;
		cin >> u >> v >> cc;
		g[u].push_back(cur);
		c[cur] = cc;
		t[cur++] = v;
		g[v].push_back(cur);
		c[cur] = cc;
		t[cur++] = u;
	}
	cout << dinic() << endl;
	cin >> n;
	return 0;
}
