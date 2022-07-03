#include <stdio.h>

int main() {
	int N, K;

	scanf("%d %d", &N, &K);

	int p[N];

	for (int i = 0; i < N; i++) {
		scanf("%d", &p[i]);
	}

	int *map = malloc((K + 1) * sizeof());
	int[K + 1];

	map[0] = 0; // technicality, απλά για να τακτοποιήσω τα στοιχεία του a που είναι ίσα με K

	for (int i = 1; i < K + 1; i++) {
		map[i] = N + 1;
	}

	long int queue[N];

	for (int i = 0; i < N; i++) {
		queue[i] = 0;
	}

	int answer = N + 1;

	// Για κάθε στήλη:
	for (int col = -1; col < N - 1; col++) {
		int i = col + 1;

		int sum = 0;
		// Τρέξε την γραμμή για να δεις μήπως υπάρχει το συμπληρωματικό
		for (int j = i; j < N; j++) {
			sum += p[j];

			int target = K - sum;

			if (target < 0) {
				break;
			}

			int firstLength = j - i + 1;
			int secondLength = map[target];
			int totalLength = firstLength + secondLength;
			answer = answer < totalLength ? answer : totalLength;
		}

		for (int k = 0, l = i + 1; k <= i; k++, l--) {
			long int s = (queue[k] += p[i]);

			if (s <= K) {
				map[s] = map[s] < l ? map[s] : l;
			}
		}
	}

	printf("%d\n", answer == N + 1 ? -1 : answer);
}
