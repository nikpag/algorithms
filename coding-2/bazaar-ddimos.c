#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 16000000000
#define N_MAX 5001
#define M_MAX 1501

unsigned long min(unsigned long a, unsigned long b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

struct Pair {
	int first;
	unsigned long second;
};

struct Pair Pair(int first, unsigned long second) {
	struct Pair ret;

	ret.first = first;
	ret.second = second;

	return ret;
}

struct Dim {
	int offersI, offersJ, offersK;
	int offerSizesI, offerSizesJ;
	int bestChoicesI, bestChoicesJ, bestChoicesK;
	int bestChoiceSizesI, bestChoiceSizesJ;
	int knapsackI, knapsackJ;
};

struct Dim Dim(int offersI, int offersJ, int offersK, int offerSizesI, int offerSizesJ, int bestChoicesI, int bestChoicesJ, int bestChoicesK, int bestChoiceSizesI, int bestChoiceSizesJ, int knapsackI, int knapsackJ) {
	struct Dim ret;

	ret.offersI = offersI;
	ret.offersJ = offersJ;
	ret.offersK = offersK;

	ret.offerSizesI = offerSizesI;
	ret.offerSizesJ = offerSizesJ;

	ret.bestChoicesI = bestChoicesI;
	ret.bestChoicesJ = bestChoicesJ;
	ret.bestChoicesK = bestChoicesK;

	ret.bestChoiceSizesI = bestChoiceSizesI;
	ret.bestChoiceSizesJ = bestChoiceSizesJ;

	ret.knapsackI = knapsackI;
	ret.knapsackJ = knapsackJ;

	return ret;
}

long from3to1(long i, long j, long k, long I, long J, long K) {
	return i * J * K + j * K + k;
}

long from2to1(long i, long j, long I, long J) {
	// printf("i = %lu\n", i);
	// printf("J = %lu\n", J);
	// printf("j = %lu\n", j);
	// printf("product = %lu\n", i * J + j);
	return i * J + j;
}

void knapsackFunction(int x, int y, int M, int N, struct Pair offers[], int offerSizes[], unsigned long bestChoices[], int bestChoiceSizes[], unsigned long knapsack[], struct Dim dim) {
	int I = offerSizes[from2to1(x, y, dim.offerSizesI, dim.offerSizesJ)];
	// printf("%d\n", I); okay

	int J = N;

	for (int j = 1; j <= J; j++) {
		knapsack[from2to1(0, j, dim.knapsackI, dim.knapsackJ)] = INFINITY;
		// printf("%lu\n", knapsack[from2to1(0, j, dim.knapsackI, dim.knapsackJ)]); okay
	}

	for (int i = 0; i <= I; i++) {
		knapsack[from2to1(i, 0, dim.knapsackI, dim.knapsackJ)] = 0;
		// printf("%lu\n", knapsack[from2to1(i, 0, dim.knapsackI, dim.knapsackJ)]); okay
	}

	for (int i = 1; i <= I; i++) {
		int quantity = offers[from3to1(x, y, i - 1, dim.offersI, dim.offersJ, dim.offersK)].first;
		// printf("%d\n", quantity); okay

		int price = offers[from3to1(x, y, i - 1, dim.offersI, dim.offersJ, dim.offersK)].second;
		// printf("%d\n", price); okay

		for (int j = 1; j <= J; j++) {
			// printf("knapFunc, j = %d\n", j);
			// printf("knapFunc, quantity = %d\n", quantity);
			unsigned long firstMin = knapsack[from2to1(i - 1, max(0, j - quantity), dim.knapsackI, dim.knapsackJ)] + price;
			// printf("firstMin = %lu\n", firstMin);
			unsigned long secondMin = knapsack[from2to1(i - 1, j, dim.knapsackI, dim.knapsackJ)];
			// printf("secondMin = %lu\n", secondMin);
			knapsack[from2to1(i, j, dim.knapsackI, dim.knapsackJ)] = min(knapsack[from2to1(i - 1, max(0, j - quantity), dim.knapsackI, dim.knapsackJ)] + price, knapsack[from2to1(i - 1, j, dim.knapsackI, dim.knapsackJ)]);
			// printf("%ld\n", knapsack[from2to1(i, j, dim.knapsackI, dim.knapsackJ)]);
		}
	}
	for (int j = 0; j <= J; j++) {
		int *index = &bestChoiceSizes[from2to1(x, y, dim.bestChoiceSizesI, dim.bestChoiceSizesJ)];
		// // printf("%d ", *index);
		bestChoices[from3to1(x, y, (*index)++, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] = knapsack[from2to1(I, j, dim.knapsackI, dim.knapsackJ)];
		// printf("%d\n", bestChoices[from3to1(x, y, (*index)++, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)]);
	}
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	int offersI = 4, offersJ = 4, offersK = M;
	int offerSizesI = 4, offerSizesJ = 4;

	int bestChoicesI = 4, bestChoicesJ = 4, bestChoicesK = N + 1;
	int bestChoiceSizesI = 4, bestChoiceSizesJ = 4;

	int knapsackI = M_MAX + 1, knapsackJ = N_MAX + 1;

	struct Dim dim = Dim(offersI, offersJ, offersK, offerSizesI, offerSizesJ, bestChoicesI, bestChoicesJ, bestChoicesK, bestChoiceSizesI, bestChoiceSizesJ, knapsackI, knapsackJ);

	struct Pair *offers = malloc(sizeof(struct Pair) * dim.offersI * dim.offersJ * dim.offersK);
	int *offerSizes = calloc(dim.offerSizesI * dim.offerSizesJ, sizeof(int));

	unsigned long *bestChoices = malloc(sizeof(unsigned long) * dim.bestChoicesI * dim.bestChoicesJ * dim.bestChoicesK);
	int *bestChoiceSizes = calloc(dim.bestChoiceSizesI * dim.bestChoiceSizesJ, sizeof(int));

	unsigned long *knapsack = malloc(sizeof(unsigned long) * dim.knapsackI * dim.knapsackJ);

	for (int i = 0; i < M; i++) {
		int x;
		scanf("%d", &x);
		// printf("%d\n", x);

		char yChar;
		scanf("%c", &yChar);
		// printf("%c\n", yChar);

		int y;
		switch (yChar) {
			case 'A':
				y = 1;
				break;
			case 'B':
				y = 2;
				break;
			case 'C':
				y = 3;
				break;
		}
		// printf("%d\n", y);

		int A;
		unsigned long P;
		scanf("%d %lu", &A, &P);
		// printf("%d\n", A);
		// printf("%d\n", P);

		int *index = &offerSizes[from2to1(x, y, dim.offerSizesI, dim.offerSizesJ)];
		// printf("%d\n", *index);
		offers[from3to1(x, y, (*index)++, dim.offersI, dim.offersJ, dim.offersK)] = Pair(A, P);
		// printf("%d %d\n", offers[from3to1(x, y, (*index)++, dim.offersI, dim.offersJ, dim.offersK)].first, offers[from3to1(x, y, (*index)++, dim.offersI, dim.offersJ, dim.offersK)].second);
	}

	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			knapsackFunction(i, j, M, N, offers, offerSizes, bestChoices, bestChoiceSizes, knapsack, dim);

	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j <= N; j++) {
			bestChoices[from3to1(i, 1, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] += bestChoices[from3to1(i, 2, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] + bestChoices[from3to1(i, 3, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)];
			// printf(bestChoices[from3to1(i, 1, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)]);
		}
	}

	unsigned long answer = INFINITY;

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (N - i - j >= 0)
				answer = min(answer, bestChoices[from3to1(1, 1, i, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] + bestChoices[from3to1(2, 1, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] + bestChoices[from3to1(3, 1, N - i - j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)]);
			else
				answer = min(answer, bestChoices[from3to1(1, 1, i, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)] + bestChoices[from3to1(2, 1, j, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)]);
			// printf("%d\n", answer);
		}
	}

	// for (int i = 1; i <= 3; i++) {
	// 	for (int j = 1; j <= 3; j++) {
	// 		for (int k = 0; k < offerSizes[from2to1(i, j, dim.offerSizesI, dim.offerSizesJ)]; k++) {
	// 			printf("%d ", offers[from3to1(i, j, k, dim.offersI, dim.offersJ, dim.offersK)].first);
	// 		}
	// 		printf("\n");
	// 	}
	// }

	// for (int i = 0; i < 10; i++) {
	// 	for (int j = 0; j < 10; j++) {
	// 		printf("%d ", knapsack[from2to1(i, j, dim.knapsackI, dim.knapsackJ)]);
	// 	}
	// 	printf("\n");
	// }

	// for (int i = 1; i <= 3; i++) {
	// 	for (int j = 1; j <= 3; j++) {
	// 		for (int k = 0; k < bestChoiceSizes[from2to1(i, j, dim.bestChoiceSizesI, dim.bestChoiceSizesJ)]; k++) {
	// 			printf("%lu ", bestChoices[from3to1(i, j, k, dim.bestChoicesI, dim.bestChoicesJ, dim.bestChoicesK)]);
	// 		}
	// 		printf("\n\n");
	// 	}
	// }

	if (answer == INFINITY)
		printf("%d\n", -1);
	else
		printf("%lu\n", answer);
}
