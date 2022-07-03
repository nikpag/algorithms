#include <algorithm>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define var 10

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int full_sets, offers, type_count, type_price, minx, miny, minz, max_offers;

int merchants[var][var][var][2];

int merchantSize[var][var];

int memo[var][var][var][var];

bool cost_comparison(int first[2], int second[2]) {
	if (first[1] == second[1])
		return (first[0] > second[0]);
	return (first[1] < second[1]);
}

// int cost_comparison(const void *a, const void *b) {
// 	// int *first = ;
// 	// int *second = (int *);
// 	int *first = a;
// 	int *second = b;

// 	if (first[1] == second[1]) {
// 		if (first[0] > second[0])
// 			return -1;
// 		if (first[0] == second[0])
// 			return 0;
// 		if (first[0] < second[0])
// 			return 1;
// 	}
// 	if (first[1] < second[1])
// 		return -1;
// 	if (first[1] > second[1])
// 		return 1;
// }

unsigned salesman(int merch, int quantity, int type, int start) {
	if (quantity <= 0)
		return 0;
	if (start < max_offers && memo[type][merch][quantity][start] != -1) {
		return memo[type][merch][quantity][start];
	}
	if (start >= merchantSize[type][merch])
		return INT_MAX;
	if (merchants[type][merch][start][0] >= full_sets) {
		return memo[type][merch][quantity][start] = merchants[type][merch][start][1];
	}
	return memo[type][merch][quantity][start] = min(salesman(merch, quantity - merchants[type][merch][start][0], type, start + 1) + merchants[type][merch][start][1], salesman(merch, quantity, type, start + 1));
}

int quantity_bought(int merch, int quantity) {
	if (quantity <= 0)
		return 0;
	return salesman(merch, quantity, 0, 0) + salesman(merch, quantity, 1, 0) + salesman(merch, quantity, 2, 0);
}

int max_offers_number() {
	int max_off = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			max_off = max(max_off, merchantSize[i][j]);
		}
	}
	return max_off;
}

int full_set_number(int merch) {
	int sets_A = 0;
	int sets_B = 0;
	int sets_C = 0;
	for (int i = 0; i < merchantSize[0][merch]; i++) { /* εδώ πρέπει να μπει merchants[{0,1,2}][merch].length */
		sets_A += merchants[0][merch][i][0];
	}
	for (int i = 0; i < merchantSize[1][merch]; i++) {
		sets_B += merchants[1][merch][i][0];
	}
	for (int i = 0; i < merchantSize[2][merch]; i++) {
		sets_C += merchants[2][merch][i][0];
	}
	return min(sets_A, min(sets_B, sets_C));
}

int total_cost() {
	int sum = INT_MAX;
	for (int x = 0; x <= min(minx, full_sets); ++x) {
		for (int y = 0; y <= min(miny, full_sets - x); ++y) {
			if (minz >= full_sets - x - y) {
				sum = min(sum, quantity_bought(0, x) + quantity_bought(1, y) + quantity_bought(2, full_sets - x - y));
			}
		}
	}
	return sum;
}

int main() {
	scanf("%d %d", &full_sets, &offers);

	// merchants.resize(3);
	// for (int i = 0; i < 3; ++i) {
	// 	merchants[i].resize(3);
	// }

	char type_id[2];
	for (int i = 0; i < offers; ++i) {
		scanf("%c %c %d %d", &type_id[0], &type_id[1], &type_count, &type_price);

		int index0;

		if (type_id[1] == 'A')
			index0 = 0;
		if (type_id[1] == 'B')
			index0 = 1;
		if (type_id[1] == 'C')
			index0 = 2;

		int index1 = (int)type_id[0] - 49;

		int *index2 = &merchantSize[index0][index1];
		merchants[index0][index1][*index2][0] = type_count;
		merchants[index0][index1][*index2][1] = type_price;
		(*index2)++;
	}

	minx = full_set_number(0);
	miny = full_set_number(1);
	minz = full_set_number(2);
	if (full_sets > minx + miny + minz) {
		printf("-1\n");
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::sort(merchants[i][j].begin(), merchants[i][j].end(), cost_comparison);
		}
	}

	max_offers = max_offers_number();
	// memo.resize(3);
	// for (int i = 0; i < 3; ++i) {
	// 	memo[i].resize(3);
	// 	for (int j = 0; j < 3; ++j) {
	// 		memo[i][j].resize(full_sets + 1);
	// 		for (int k = 0; k < full_sets + 1; ++k) {
	// 			memo[i][j][k].resize(max_offers, -1);
	// 		}
	// 	}
	// }

	printf("%d\n", total_cost());

	return 0;
}
