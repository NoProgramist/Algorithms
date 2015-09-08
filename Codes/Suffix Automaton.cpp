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


struct state
{
	bool term;
	int len, link;
	int next[26];
}S[MAX << 1];
int last, cur;


void Build(string& s)
{
	cur = last = 1;
	S[cur].len = S[cur].link = S[cur].term = 0;
	++cur;
	rep(i, s.size())
	{
		int CUR = cur++;
		S[CUR].len = S[last].len + 1;
		S[CUR].term = 0;
		int P = last;
		for (; P && !S[P].next[s[i] - 'a']; P = S[P].link)
			S[P].next[s[i] - 'a'] = CUR;
		if (!P)
			S[CUR].link = 1;
		else
		{
			int Q = S[P].next[s[i] - 'a'];
			if (S[P].len + 1 == S[Q].len)
				S[CUR].link = Q;
			else
			{
				int NEW = cur++;
				S[NEW].len = S[P].len + 1;
				S[NEW].link = S[Q].link;
				S[NEW].term = 0;
				rep(j, 26)
					S[NEW].next[j] = S[Q].next[j];
				for (; P && S[P].next[s[i] - 'a'] == Q; P = S[P].link)
					S[P].next[s[i] - 'a'] = NEW;
				S[Q].link = S[CUR].link = NEW;
			}
		}
		last = CUR;
	}
	for (int P = last; P; P = S[P].link)
		S[P].term = 1;
}

bool IsSubString(string & s)
{
	int P = 1;
	rep(i, s.size())
	{
		if (!S[P].next[s[i] - 'a'])return 0;
		P = S[P].next[s[i] - 'a'];
	}
	return 1;
}


int main()
{
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;	
	Build(s);
	int m;
	cin >> m;
	rep(i, m)
	{
		cin >> s;
		cout << (IsSubString(s) ? "YES" : "NO") << '\n';
	}
	cin >> s;
	return 0;
}
