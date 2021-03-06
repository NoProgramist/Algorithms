#include <iostream>
#include <sstream>
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
#include <numeric>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <functional>
#include <math.h>
#include <utility>


#pragma comment(linker, "/STACK:133217728")

using namespace std;

vector<int> g[2222], gt[2222];
bool used[2222];
vector <int> order;
int color[2222];
void dfs(int v) {
	used[v] = 1;
	for(int i=0; i<g[v].size(); i++) {
		int to = g[v][i];
		if(!used[to]) 
			dfs(to);
	}
	order.push_back(v);
}

void dfs2(int v, int col) {
	color[v] = col;
	for(int i=0; i<gt[v].size(); i++) {
		int to = gt[v][i];
		if(!color[to])
			dfs2(to, col);
	}
}

int main() {  
	//freopen("1.docx", "r", stdin);
	//ifreopen("out.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	int n, m;
	while(cin >> n >> m) {
		for(int i=0; i<=2*n; i++)
			g[i].clear(),
			gt[i].clear();
		for(int i=0; i<m; i++) {
			int a, b;
			cin >> a >> b;
			if(a < 0) a = 2*(-a) - 1;
				else a = 2 * a - 2;
			if(b < 0) b = 2*(-b) - 1;
				else b = 2 * b - 2;
				
			g[a ^ 1].push_back(b);
			gt[b].push_back(a ^ 1);

			g[b ^ 1].push_back(a);
			gt[a].push_back(b ^ 1);
		}

		for(int i=0; i<=2*n; i++)
			used[i] = 0;
		order.clear();
		for(int i=0; i<2*n; i++)
			if(!used[i])
				dfs(i);
		int cnt = 0;
		for(int i=0; i<2*n; i++)
			color[i] = 0;
		reverse(order.begin(), order.end());
		for(int i=0; i<2*n; i++)
			if(!color[order[i]])
				dfs2(order[i], ++cnt);

		bool ok = 1;
		for(int i=0; i<2*n; i++)
			if(color[i] == color[i ^ 1])
				ok = 0;

		if(color[0] < color[1]) ok = 0;
		if(ok) cout << "yes\n"; else cout << "no\n";
		
	}
	return 0;
}