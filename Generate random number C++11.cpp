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
#include <random>

#pragma comment(linker, "/STACK:133217728")

using namespace std;

int main() {  
	ios_base::sync_with_stdio(0);
	random_device rd;
    mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10000);
	for (int i=0; i<20; ++i)
		cout << dist(mt) << endl;
	return 0;
}

