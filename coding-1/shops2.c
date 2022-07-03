#include <stdio.h>

int main() {
	int N, K;

	scanf("%d %d", &N, &K);

	int p[N];

	for (int i = 0; i < N; i++) {
		scanf("%d", &p[i]);
	}

	int map[K + 1];

	map[0] = 0;

	for (int i = 1; i < K + 1; i++) {
		map[i] = N + 1;
	}

	int queue[N];

	for (int i = 0; i < N; i++) {
		queue[i] = 0;
	}

	int answer = N + 1;

	for (int col = -1; col < N - 1; col++) {
		int i = col + 1;

		int sum = 0;
		for (int j = i; j < N; j++) {
			sum += p[j];

			if (sum > K)
				break;

			int target = K - sum;

			int totalLength = (j - i + 1) + map[target];
			answer = answer < totalLength ? answer : totalLength;
		}

		for (int k = i, l = 1; k >= 0; k--, l++) {
			int s = (queue[k] += p[i]);

			if (s > K || s < 0)
				break;

			map[s] = map[s] < l ? map[s] : l;
		}
	}

	printf("%d\n", answer == N + 1 ? -1 : answer);
}
