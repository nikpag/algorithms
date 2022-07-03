#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int sorted(int a[], int N) {
	for (int i = 0; i < N - 1; i++) {
		if (a[i] > a[i + 1])
			return false;
	}
	return true;
}

int main() {
	int a[] = {10, 2, 3, 4, 5};
	int b[] = {1, 10, 3, 4, 5};
	int c[] = {1, 2, 10, 4, 5};
	int d[] = {1, 2, 3, 10, 5};
	int e[] = {1, 2, 3, 4, 3};
	printf("%d %d %d %d %d\n", sorted(a, 5), sorted(b, 5), sorted(c, 5), sorted(d, 5), sorted(e, 5));
}
