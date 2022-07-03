#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define infinity 16000000000
#define N_max 5001
#define M_max 1501
#define mp std::make_pair
#define pb push_back

int N, M, A;
unsigned long P;
std::vector<std::pair<int, unsigned long>> offers[4][4];
std::vector<unsigned long> best_choices[4][4];
unsigned long int knapsack_[M_max + 1][N_max + 1];

void knapsack(int merchant, int object) {
	int I = offers[merchant][object].size();

	// printf("%d\n", I); okay

	int J = N;

	for (int j = 1; j <= J; j++) {
		knapsack_[0][j] = infinity;
		// printf("%lu\n", knapsack_[0][j]);
	}
	for (int i = 0; i <= I; i++) {
		knapsack_[i][0] = 0;
		// printf("%lu\n", knapsack_[i][0]); okay
	}
	for (int i = 1; i <= I; i++) {
		int quantity = offers[merchant][object][i - 1].first;
		// printf("%d\n", quantity); okay
		int price = offers[merchant][object][i - 1].second;
		// printf("%d\n", price); okay
		for (int j = 1; j <= J; j++) {
			// printf("knapFunc, j = %d\n", j);
			// printf("knapFunc, quantity = %d\n", quantity);
			knapsack_[i][j] = std::min(knapsack_[i - 1][std::max(0, j - quantity)] + price, knapsack_[i - 1][j]);
			// printf("%lu\n", knapsack_[i][j]);
		}
	}
	for (int j = 0; j <= J; j++) {
		best_choices[merchant][object].pb(knapsack_[I][j]);
		// printf("%d\n", knapsack_[I][j]);
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int merchant;
		scanf("%d", &merchant);
		// printf("%d\n", merchant);
		char equip = getchar();
		// printf("%c\n", equip);
		int object;
		switch (equip) {
			case 'A':
				object = 1;
				break;
			case 'B':
				object = 2;
				break;
			case 'C':
				object = 3;
				break;
		}
		// printf("%d\n", object);

		scanf("%d %lu", &A, &P);
		// printf("%d %d\n", A, P);

		offers[merchant][object].pb(mp(A, P));
		// printf("%d %d\n", mp(A, P).first, mp(A, P).second);
	}
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			knapsack(i, j);

	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j <= N; j++) {
			best_choices[i][1][j] += best_choices[i][2][j] + best_choices[i][3][j];
			// printf("%d\n", best_choices[i][1][j]);
		}
	}
	unsigned long answer = infinity;

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (N - i - j >= 0)
				answer = std::min(answer, best_choices[1][1][i] + best_choices[2][1][j] + best_choices[3][1][N - i - j]);
			else
				answer = std::min(answer, best_choices[1][1][i] + best_choices[2][1][j]);
		}
		// printf("%d\n", answer);
	}

	// for (int i = 0; i < 10; i++) {
	// 	for (int j = 0; j < 10; j++) {
	// 		printf("%lu ", knapsack_[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// for (int i = 1; i <= 3; i++) {
	// 	for (int j = 1; j <= 3; j++) {
	// 		for (int k = 0; k < best_choices[i][j].size(); k++) {
	// 			printf("%lu ", best_choices[i][j][k]);
	// 		}
	// 		printf("\n\n");
	// 	}
	// }

	if (answer == infinity)
		printf("%d\n", -1);
	else
		printf("%lu\n", answer);
}
