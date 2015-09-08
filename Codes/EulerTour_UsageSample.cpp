define _CRT_SECURE_NO_WARNINGS
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


typedef vector < vector<int> > graph;

vector<int> dfs_list;
vector<int> ribs_list;
vector<int> h;
vector<int> pred;
vector<int> reb;

void dfs(int v, const graph & g, const graph & rib_ids, int cur_h = 1, int p = -1, int id = 0)
{
	h[v] = cur_h;
	pred[v] = p;
	reb[v] = id;
	dfs_list.push_back(v);
	for (size_t i = 0; i<g[v].size(); ++i)
		if (h[g[v][i]] == -1)
		{
			ribs_list.push_back(rib_ids[v][i]);
			dfs(g[v][i], g, rib_ids, cur_h + 1, v, rib_ids[v][i]);
			ribs_list.push_back(rib_ids[v][i]);
			dfs_list.push_back(v);
		}
}

vector<int> lca_tree;
vector<int> first;

void lca_tree_build(int i, int l, int r)
{
	if (l == r)
		lca_tree[i] = dfs_list[l];
	else
	{
		int m = (l + r) >> 1;
		lca_tree_build(i + i, l, m);
		lca_tree_build(i + i + 1, m + 1, r);
		int lt = lca_tree[i + i], rt = lca_tree[i + i + 1];
		lca_tree[i] = h[lt] < h[rt] ? lt : rt;
	}
}

void lca_prepare(int n)
{
	lca_tree.assign(dfs_list.size() * 8, -1);
	lca_tree_build(1, 0, (int)dfs_list.size() - 1);

	first.assign(n, -1);
	for (int i = 0; i < (int)dfs_list.size(); ++i)
	{
		int v = dfs_list[i];
		if (first[v] == -1)  first[v] = i;
	}
}

int lca_tree_query(int i, int tl, int tr, int l, int r)
{
	if (tl == l && tr == r)
		return lca_tree[i];
	int m = (tl + tr) >> 1;
	if (r <= m)
		return lca_tree_query(i + i, tl, m, l, r);
	if (l > m)
		return lca_tree_query(i + i + 1, m + 1, tr, l, r);
	int lt = lca_tree_query(i + i, tl, m, l, m);
	int rt = lca_tree_query(i + i + 1, m + 1, tr, m + 1, r);
	return h[lt] < h[rt] ? lt : rt;
}

int lca(int a, int b)
{
	if (first[a] > first[b])  swap(a, b);
	return lca_tree_query(1, 0, (int)dfs_list.size() - 1, first[a], first[b]);
}


vector<int> first1, first2;
vector<int> rib_used;
vector<ll> tree1, tree2;

void query_prepare(int n)
{
	first1.assign(n - 1, -1);
	first2.assign(n - 1, -1);
	for (int i = 0; i < (int)ribs_list.size(); ++i)
	{
		int j = ribs_list[i];
		if (first1[j] == -1)
			first1[j] = i;
		else
			first2[j] = i;
	}

	rib_used.assign(n - 1, 0);
	tree1.assign(ribs_list.size() * 8, 0);
	tree2.assign(ribs_list.size() * 8, 0);
}

void sum_tree_update(vector<ll> & tree, int i, int l, int r, int j, int delta)
{
	tree[i] += delta;
	if (l < r)
	{
		int m = (l + r) >> 1;
		if (j <= m)
			sum_tree_update(tree, i + i, l, m, j, delta);
		else
			sum_tree_update(tree, i + i + 1, m + 1, r, j, delta);
	}
}

ll sum_tree_query(const vector<ll> & tree, int i, int tl, int tr, int l, int r)
{
	if (l > r || tl > tr)  return 0;
	if (tl == l && tr == r)
		return tree[i];
	int m = (tl + tr) >> 1;
	if (r <= m)
		return sum_tree_query(tree, i + i, tl, m, l, r);
	if (l > m)
		return sum_tree_query(tree, i + i + 1, m + 1, tr, l, r);
	return sum_tree_query(tree, i + i, tl, m, l, m)
		+ sum_tree_query(tree, i + i + 1, m + 1, tr, m + 1, r);
}

ll query(int v1, int v2)
{
	return sum_tree_query(tree1, 1, 0, (int)ribs_list.size() - 1, first[v1], first[v2] - 1)
		- sum_tree_query(tree2, 1, 0, (int)ribs_list.size() - 1, first[v1], first[v2] - 1);
}

int f[MAX];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--){
		int n, m;
		cin >> n >> m;
		n++;
		graph g(n), rib_ids(n);
		rep(i, n - 1)
			cin >> f[i + 1];
		g[0].push_back(1);
		g[1].push_back(0);
		rib_ids[0].push_back(0);
		rib_ids[1].push_back(0);
		FOR(i, 1, n - 2)
		{
			int v1, v2;
			cin >> v1 >> v2;
			g[v1].push_back(v2);
			g[v2].push_back(v1);
			rib_ids[v1].push_back(i);
			rib_ids[v2].push_back(i);
		}
		h.assign(n, -1);
		reb.assign(n, -1);
		pred.assign(n, -1);
		dfs_list.clear();
		ribs_list.clear();
		dfs(0, g, rib_ids);
		lca_prepare(n);
		query_prepare(n);
		FOR(i, 1, n - 1)
		{
			rib_used[reb[i]] = -f[i];
			sum_tree_update(tree1, 1, 0, (int)ribs_list.size() - 1, first1[reb[i]], -f[i]);
			sum_tree_update(tree2, 1, 0, (int)ribs_list.size() - 1, first2[reb[i]], -f[i]);
		}


		FOR(q, 1, m)
		{
			char ch;
			int x, y;
			cin >> ch;
			if (ch == 'P') {
				cin >> x;
				sum_tree_update(tree1, 1, 0, (int)ribs_list.size() - 1, first1[reb[x]], q - rib_used[reb[x]]);
				sum_tree_update(tree2, 1, 0, (int)ribs_list.size() - 1, first2[reb[x]], q - rib_used[reb[x]]);
				rib_used[reb[x]] = q;
			}
			else {
				cin >> x >> y;
				int l = lca(x, y);
				ll result = q * 1ll * (h[x] + h[y] - 2 * h[l] + 1) - query(l, x) - query(l, y) - rib_used[reb[l]];
				cout << result << '\n';
			}
		}
	}

}
