#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Portal {
	int a, b, w;
};

int compare(const void *elem1, const void *elem2) {
	struct Portal *p1 = (struct Portal *)elem1;
	struct Portal *p2 = (struct Portal *)elem2;

	if (p1->w < p2->w)
		return -1;
	if (p1->w == p2->w)
		return 0;
	if (p1->w > p2->w)
		return 1;
}

bool sorted(struct Portal a[], int N) {
	for (int i = 0; i < N - 1; i++) {
		if (a[i].w > a[i + 1].w)
			return false;
	}
	return true;
}

int _find(int x, int parent[]) {
	if (x != parent[x]) {
		parent[x] = _find(parent[x], parent);
	}
	return parent[x];
}

void _union(int x, int y, int parent[], int rank[]) {
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
	for (int i = 1; i <= N; i++) {
		if (_find(i, parent) != _find(c[i], parent)) {
			return false;
		}
	}
	return true;
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	int *c = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &c[i]);
	}

	struct Portal *p = (struct Portal *)malloc(M * sizeof(struct Portal));

	for (int j = 0; j < M; j++) {
		scanf("%d %d %d", &p[j].a, &p[j].b, &p[j].w);
	}

	if (!sorted(p, M)) {
		qsort(p, M, sizeof(struct Portal), compare);
	}

	int parent[N + 1];
	int rank[N + 1];

	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		rank[i] = 1;
	}

	for (int i = M - 1; i >= 0; i--) {
		_union(p[i].a, p[i].b, parent, rank);
		if (sufficient(c, parent, N)) {
			printf("%d\n", p[i].w);
			return 0;
		}
	}
}
