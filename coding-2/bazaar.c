/* includes */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* constant definitions */
#define N_MAX 5000
#define M_MAX 1500

/* macro definitions */
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

/* Struct declarations */
struct PairStruct {
	int first;
	int second;
};

struct TypeIDStruct {
	int number;
	char letter;
};

/* global variables */
int setsOfArmor, minimumOfX, minimumOfY, minimumOfZ, maximumOfOffers;

/* Array declarations */
int dpArray[3][3][N_MAX][M_MAX];
struct PairStruct merchantArray[3][3][M_MAX];
int merchantArraySize[3][3];

/* function declarations */
int costCompareFunction(const void *, const void *);
int maximumOfOffersNumber();
int numberOfFullSets(int);
int quantityOfMerchandiseBought(int, int);
unsigned salesmanFunction(int, int, int, int);
int totalCostFunction();

int main()
{
	int offersNumber;
	scanf("%d %d", &setsOfArmor, &offersNumber);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			merchantArraySize[i][j] = 0;
		}
	}

	int index0;
	int index1;
	int *index2;

	struct TypeIDStruct typeOfMerchandiseID;
	int countOfType, priceOfType;

	for (int i = 0; i < offersNumber; ++i) {
		scanf("%d %c %d %d", &typeOfMerchandiseID.number, &typeOfMerchandiseID.letter, &countOfType, &priceOfType);

		switch (typeOfMerchandiseID.letter) {
			case 'A':
				index0 = 0;
				break;
			case 'B':
				index0 = 1;
				break;
			case 'C':
				index0 = 2;
				break;
		}

		index1 = typeOfMerchandiseID.number - 1;

		index2 = &merchantArraySize[index0][index1];

		merchantArray[index0][index1][*index2].first = countOfType;
		merchantArray[index0][index1][*index2].second = priceOfType;
		(*index2)++;
	}

	minimumOfX = numberOfFullSets(0);
	minimumOfY = numberOfFullSets(1);
	minimumOfZ = numberOfFullSets(2);

	if (setsOfArmor > minimumOfX + minimumOfY + minimumOfZ) {
		printf("-1\n");
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			qsort(&merchantArray[i][j][0], merchantArraySize[i][j], sizeof(struct PairStruct), costCompareFunction);
		}
	}

	maximumOfOffers = maximumOfOffersNumber();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < setsOfArmor + 1; k++) {
				for (int l = 0; l < maximumOfOffers; l++) {
					dpArray[i][j][k][l] = -1;
				}
			}
		}
	}

	printf("%d\n", totalCostFunction());

	return 0;
}

/* function definitions */
int costCompareFunction(const void *a, const void *b)
{
	const struct PairStruct *A = (struct PairStruct *)a;
	const struct PairStruct *B = (struct PairStruct *)b;

	if (A->second == B->second) {
		if (A->first > B->first)
			return -1;
		if (A->first == B->first)
			return 0;
		if (A->first < B->first)
			return 1;
	}
	if (A->second < B->second)
		return -1;
	if (A->second > B->second)
		return 1;
}

unsigned salesmanFunction(int merchandise, int quantityOfMerchandise, int typeOfMerchandise, int startingIndex)
{
	if (quantityOfMerchandise <= 0) {
		return 0;
	}
	else if (startingIndex < maximumOfOffers && dpArray[typeOfMerchandise][merchandise][quantityOfMerchandise][startingIndex] != -1) {
		return dpArray[typeOfMerchandise][merchandise][quantityOfMerchandise][startingIndex];
	}
	else if (startingIndex >= merchantArraySize[typeOfMerchandise][merchandise]) {
		return INT_MAX;
	}
	else if (merchantArray[typeOfMerchandise][merchandise][startingIndex].first >= setsOfArmor) {
		return dpArray[typeOfMerchandise][merchandise][quantityOfMerchandise][startingIndex] = merchantArray[typeOfMerchandise][merchandise][startingIndex].second;
	}
	else {
		return dpArray[typeOfMerchandise][merchandise][quantityOfMerchandise][startingIndex] = min(salesmanFunction(merchandise, quantityOfMerchandise - merchantArray[typeOfMerchandise][merchandise][startingIndex].first, typeOfMerchandise, startingIndex + 1) + merchantArray[typeOfMerchandise][merchandise][startingIndex].second, salesmanFunction(merchandise, quantityOfMerchandise, typeOfMerchandise, startingIndex + 1));
	}
}

int quantityOfMerchandiseBought(int merchandise, int quantityOfMerchandise)
{
	return ((quantityOfMerchandise <= 0) ? 0 : salesmanFunction(merchandise, quantityOfMerchandise, 0, 0) + salesmanFunction(merchandise, quantityOfMerchandise, 1, 0) + salesmanFunction(merchandise, quantityOfMerchandise, 2, 0));
}

int maximumOfOffersNumber()
{
	int maximumOffer = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			maximumOffer = max(maximumOffer, merchantArraySize[i][j]);
		}
	}
	return maximumOffer;
}

int numberOfFullSets(int merchandise)
{
	int setsOfA = 0;
	int setsOfB = 0;
	int setsOfC = 0;
	for (int i = 0; i < merchantArraySize[0][merchandise]; i++) {
		setsOfA += merchantArray[0][merchandise][i].first;
	}
	for (int i = 0; i < merchantArraySize[1][merchandise]; i++) {
		setsOfB += merchantArray[1][merchandise][i].first;
	}
	for (int i = 0; i < merchantArraySize[2][merchandise]; i++) {
		setsOfC += merchantArray[2][merchandise][i].first;
	}
	return min(setsOfA, min(setsOfB, setsOfC));
}

int totalCostFunction()
{
	int sum = INT_MAX;
	for (int x = 0; x <= min(minimumOfX, setsOfArmor); x++) {
		for (int y = 0; y <= min(minimumOfY, setsOfArmor - x); y++) {
			if (minimumOfZ >= setsOfArmor - x - y) {
				sum = min(sum, quantityOfMerchandiseBought(0, x) + quantityOfMerchandiseBought(1, y) + quantityOfMerchandiseBought(2, setsOfArmor - x - y));
			}
		}
	}
	return sum;
}
