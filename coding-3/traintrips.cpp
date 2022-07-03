#if 1
#include <set>
#include <vector>
#include <stdio.h>
#endif

int i;
int thisIsDK = 10001;
int thisNumberIsN;
int *intAddressToScanFrom;

unsigned long Q;
unsigned long thisIsTheArrayForQueries[10001];

unsigned long *unsignedLongAddressToScanFrom;
unsigned long *distanceArray;

bool loopCondition;
bool ifCondition;

struct thisStructIsPair {
	unsigned long firstNumber;
	int secondNumber;

	thisStructIsPair(unsigned long firstNumber, int secondNumber);
	friend bool operator<(const thisStructIsPair &p1, const thisStructIsPair &p2);
};

std::set<thisStructIsPair> roomThatEveryoneWaits;

thisStructIsPair::thisStructIsPair(unsigned long firstNumber, int secondNumber)
{
	this->firstNumber = firstNumber;
	this->secondNumber = secondNumber;
}

bool operator<(const thisStructIsPair &p1, const thisStructIsPair &p2)
{
	bool valueToReturn = false;
	ifCondition = p1.firstNumber < p2.firstNumber;
	if (ifCondition) {
		valueToReturn = true;
	}
	else {
		ifCondition = p1.firstNumber == p2.firstNumber;
		if (ifCondition) {
			ifCondition = p1.secondNumber < p2.secondNumber;
			if (ifCondition) {
				valueToReturn = true;
			}
		}
	}
	return valueToReturn;
}

int main()
{
	i = 0;
	loopCondition = i < 10001;
	while (loopCondition) {
		thisIsTheArrayForQueries[i] = -1;
		i = i + 1;
		loopCondition = i < 10001;
	}

	unsignedLongAddressToScanFrom = &Q;
	intAddressToScanFrom = &thisNumberIsN;
	scanf("%d %lu", intAddressToScanFrom, unsignedLongAddressToScanFrom);

	distanceArray = new unsigned long[thisNumberIsN + 1];

	i = 1;
	unsigned long di;
	loopCondition = i <= thisNumberIsN;
	while (loopCondition) {
		unsignedLongAddressToScanFrom = &di;
		scanf("%lu", unsignedLongAddressToScanFrom);
		distanceArray[i] = di;
		ifCondition = di < thisIsDK;
		if (ifCondition) {
			thisIsDK = di;
		}
		i = i + 1;
		loopCondition = i <= thisNumberIsN;
	}

	thisIsTheArrayForQueries[0] = 0;

	roomThatEveryoneWaits.insert(thisStructIsPair(thisIsTheArrayForQueries[0], 0));

	loopCondition = !roomThatEveryoneWaits.empty();
	while (loopCondition) {
		thisStructIsPair headOfEverything = *roomThatEveryoneWaits.begin();
		unsigned long currentThing = headOfEverything.secondNumber;
		int distanceSum = headOfEverything.firstNumber;
		roomThatEveryoneWaits.erase(headOfEverything);

		i = 1;
		loopCondition = i <= thisNumberIsN;
		while (i <= thisNumberIsN) {
			int thisIsTheNewDistance = distanceSum + distanceArray[i];
			int thisIsTheNewNode = (currentThing + distanceArray[i]) % thisIsDK;

			ifCondition = !(-1 != thisIsTheArrayForQueries[thisIsTheNewNode] && thisIsTheArrayForQueries[thisIsTheNewNode] <= thisIsTheNewDistance);
			if (ifCondition) {
				roomThatEveryoneWaits.erase(thisStructIsPair(thisIsTheArrayForQueries[thisIsTheNewNode], thisIsTheNewNode));
				thisIsTheArrayForQueries[thisIsTheNewNode] = thisIsTheNewDistance;
				roomThatEveryoneWaits.insert(thisStructIsPair(thisIsTheArrayForQueries[thisIsTheNewNode], thisIsTheNewNode));
			}

			i = i + 1;
			loopCondition = i <= thisNumberIsN;
		}
		loopCondition = !roomThatEveryoneWaits.empty();
	}

	i = 0;
	loopCondition = i < Q;
	while (loopCondition) {
		unsigned long q;
		unsignedLongAddressToScanFrom = &q;
		scanf("%lu", unsignedLongAddressToScanFrom);
		ifCondition = thisIsTheArrayForQueries[q % thisIsDK] > q;
		if (ifCondition) {
			printf("NO\n");
		}
		else {
			printf("YES\n");
		}

		i = i + 1;
		loopCondition = i < Q;
	}
}
