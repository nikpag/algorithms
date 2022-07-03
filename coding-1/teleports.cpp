#include <algorithm>
#include <iostream>

using namespace std;

struct Portal {
	int a, b, w;
};

bool compare(Portal p1, Portal p2) {
	return p1.w < p2.w;
}

int _find(int x, int parent[]) {
	// cout << "Calling find" << endl;
	if (x != parent[x]) {
		parent[x] = _find(parent[x], parent);
	}
	return parent[x];
}

void _union(int x, int y, int parent[], int rank[]) {
	// cout << "Calling union" << endl;
	int r1 = _find(x, parent);
	int r2 = _find(y, parent);

	if (r1 == r2)
		return;

	if (rank[r1] < rank[r2]) {
		rank[r2] += rank[r1];
		parent[r1] = r2;
	}
	else {
		rank[r1] += rank[r2];
		parent[r2] = r1;
	}
}

bool sufficient(int c[], int parent[], int N) {
	// cout << "Calling sufficient" << endl;
	for (int i = 1; i <= N; i++) {
		if (_find(i, parent) != _find(c[i], parent)) {
			return false;
		}
	}
	return true;
}

int main() {
	int N, M;
	cin >> N >> M;

	int *c = new int[N + 1];

	for (int i = 1; i <= N; i++) {
		cin >> c[i];
	}

	Portal *p = new Portal[M];

	for (int j = 0; j < M; j++) {
		cin >> p[j].a >> p[j].b >> p[j].w;
	}

	sort(p, p + M, compare);

	int currBest = 0;

	int left = 0, right = M; // might need left = -1, right = M + 1

	while (left <= right) {

		int mid = (left + right) / 2;

		// cout << "mid width: " << p[mid].w << endl;

		int parent[N + 1];
		int rank[N + 1];

		for (int i = 1; i <= N; i++) {
			parent[i] = i;
			rank[i] = 1; // should it be i?
		}

		for (int j = mid; j < M; j++) {
			_union(p[j].a, p[j].b, parent, rank);
		}

		if (sufficient(c, parent, N)) {
			// cout << p[mid].w << " is sufficient" << endl;
			currBest = p[mid].w;
			left = mid + 1;
		}
		else {
			// cout << p[mid].w << " is not sufficient" << endl;
			right = mid - 1;
		}
	}

	cout << currBest << endl;
}
