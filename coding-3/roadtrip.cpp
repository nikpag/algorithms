#include <cstdio>
#include <algorithm>
#include <vector>

#define max(x, y) (((x) > (y)) ? (x) : (y))

void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

template <typename T, typename G>
struct thisIsThePairStruct {
	thisIsThePairStruct()
	{
		this->firstNumber = 0;
		this->secondNumber = 0;
	}

	thisIsThePairStruct(T firstNumber, G secondNumber)
	{
		this->firstNumber = firstNumber;
		this->secondNumber = secondNumber;
	}

	friend bool operator<(const thisIsThePairStruct<T, G> &p1, const thisIsThePairStruct<T, G> &p2)
	{
		bool retVal = false;
		bool ifCondition = p1.firstNumber < p2.firstNumber;
		if (ifCondition) {
			retVal = true;
		}
		else {
			ifCondition = p1.firstNumber == p2.firstNumber;
			if (ifCondition) {
				ifCondition = p1.secondNumber < p2.secondNumber;
				if (ifCondition) {
					retVal = true;
				}
			}
		}
		return retVal;
	}
	T firstNumber;
	G secondNumber;
	bool ifCondition;
};

std::vector<thisIsThePairStruct<int, thisIsThePairStruct<int, int>>> edgeThingy;
int thisIsN, thisIsM, thisIsTheParentMatrix[50000 + 1], thisIsTheRankMatrix[50000 + 1];

int find(int thisIsUParam)
{
	bool ifCondition = thisIsTheParentMatrix[thisIsUParam] == thisIsUParam;
	if (ifCondition)
		return thisIsUParam;
	return thisIsTheParentMatrix[thisIsUParam] = find(thisIsTheParentMatrix[thisIsUParam]);
}

std::vector<thisIsThePairStruct<int, int>> treesEverywhere[50000 + 1];

int Q, depthArrayThing[50000 + 1], P[50000 + 1][17], RMQMan[50000 + 1][17];

void dfs(int thisIsUParam, int p)
{
	int i;
	bool ifCondition;
	bool loopCondition;

	P[thisIsUParam][0] = p;

	i = 0;
	loopCondition = i < treesEverywhere[thisIsUParam].size();
	while (loopCondition) {
		int thisIsVParam = treesEverywhere[thisIsUParam][i].firstNumber, w = treesEverywhere[thisIsUParam][i].secondNumber;
		ifCondition = thisIsVParam == p;
		if (ifCondition) {
			i = i + 1;
			loopCondition = i < treesEverywhere[thisIsUParam].size();
			continue;
		}
		depthArrayThing[thisIsVParam] = depthArrayThing[thisIsUParam] + 1;
		RMQMan[thisIsVParam][0] = w;
		dfs(thisIsVParam, thisIsUParam);
		i = i + 1;
		loopCondition = i < treesEverywhere[thisIsUParam].size();
	}
}

int main(void)
{
	int thisIsUParam, thisIsVParam, w, i, j;
	scanf("%d%d", &thisIsN, &thisIsM);
	bool ifCondition, loopCondition, loopConditionInner;

	i = 1;
	loopCondition = i <= thisIsN;
	while (loopCondition) {
		thisIsTheParentMatrix[i] = i;
		i = i + 1;
		loopCondition = i <= thisIsN;
	}

	i = 1;
	loopCondition = i <= thisIsM;
	while (loopCondition) {
		scanf("%d%d%d", &thisIsUParam, &thisIsVParam, &w);
		edgeThingy.push_back(thisIsThePairStruct<int, thisIsThePairStruct<int, int>>(w, thisIsThePairStruct<int, int>(thisIsUParam, thisIsVParam)));
		i = i + 1;
		loopCondition = i <= thisIsM;
	}

	sort(edgeThingy.begin(), edgeThingy.end());
	i = 0;
	loopCondition = i < edgeThingy.size();
	while (loopCondition) {
		thisIsUParam = edgeThingy[i].secondNumber.firstNumber, thisIsVParam = edgeThingy[i].secondNumber.secondNumber, w = edgeThingy[i].firstNumber;
		ifCondition = find(thisIsUParam) != find(thisIsVParam);
		if (ifCondition) {
			thisIsUParam = find(thisIsUParam);
			thisIsVParam = find(thisIsVParam);
			ifCondition = thisIsTheRankMatrix[thisIsUParam] > thisIsTheRankMatrix[thisIsVParam];
			if (ifCondition) {
				thisIsTheParentMatrix[thisIsVParam] = thisIsUParam;
			}
			else {
				thisIsTheParentMatrix[thisIsUParam] = thisIsVParam;
				ifCondition = thisIsTheRankMatrix[thisIsUParam] == thisIsTheRankMatrix[thisIsVParam];
				if (ifCondition)
					thisIsTheRankMatrix[thisIsVParam]++;
			}
			treesEverywhere[thisIsUParam].push_back(thisIsThePairStruct<int, int>(thisIsVParam, w));
			treesEverywhere[thisIsVParam].push_back(thisIsThePairStruct<int, int>(thisIsUParam, w));
		}

		i = i + 1;
		loopCondition = i < edgeThingy.size();
	}

	dfs(1, -1);

	j = 1;
	loopCondition = (1 << j) <= thisIsN;
	while (loopCondition) {
		i = 1;
		loopConditionInner = i <= thisIsN;
		while (loopConditionInner) {
			P[i][j] = P[P[i][j - 1]][j - 1];
			RMQMan[i][j] = max(RMQMan[P[i][j - 1]][j - 1], RMQMan[i][j - 1]);
			i = i + 1;
			loopConditionInner = i <= thisIsN;
		}
		j = j + 1;
		loopCondition = (1 << j) <= thisIsN;
	}
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d%d", &thisIsUParam, &thisIsVParam);

		int savedU = thisIsUParam;
		int savedV = thisIsVParam;
		int lcaRet;
		int lg = 0;
		ifCondition = depthArrayThing[thisIsUParam] < depthArrayThing[thisIsVParam];
		if (ifCondition) {
			swap(thisIsUParam, thisIsVParam);
		}
		ifCondition = !depthArrayThing[thisIsUParam];
		if (ifCondition) {
			lcaRet = thisIsUParam;
			goto ret;
		}

		lg = 0;
		loopCondition = (1 << lg) <= depthArrayThing[thisIsUParam];
		while (loopCondition) {
			lg = lg + 1;
			loopCondition = (1 << lg) <= depthArrayThing[thisIsUParam];
		}
		lg--;
		i = lg;
		loopCondition = i >= 0;
		while (loopCondition) {
			ifCondition = depthArrayThing[thisIsUParam] - (1 << i) >= depthArrayThing[thisIsVParam];
			if (ifCondition) {
				thisIsUParam = P[thisIsUParam][i];
			}

			i = i - 1;
			loopCondition = i >= 0;
		}
		ifCondition = thisIsUParam == thisIsVParam;
		if (ifCondition) {
			lcaRet = thisIsUParam;
			goto ret;
		}
		i = lg;
		loopCondition = i >= 0;
		while (loopCondition) {
			ifCondition = !(P[thisIsUParam][i] == P[thisIsVParam][i] || P[thisIsUParam][i] == -1);
			if (ifCondition) {
				thisIsUParam = P[thisIsUParam][i];
				thisIsVParam = P[thisIsVParam][i];
			}
			i = i - 1;
			loopCondition = i >= 0;
		}
		lcaRet = P[thisIsUParam][0];
		goto ret;
	ret:
		thisIsUParam = savedU;
		thisIsVParam = savedV;

		int LCA = lcaRet, uv, uu, maxi = 0, resultThing;
		uv = 0;

		loopCondition = (1 << uv) <= depthArrayThing[thisIsVParam];
		while (loopCondition) {
			uv = uv + 1;
			loopCondition = (1 << uv) <= depthArrayThing[thisIsVParam];
		}

		uv--;
		uu = 0;
		loopCondition = (1 << uu) <= depthArrayThing[thisIsUParam];
		while (loopCondition) {
			uu = uu + 1;
			loopCondition = (1 << uu) <= depthArrayThing[thisIsUParam];
		}
		uu--;
		ifCondition = !(depthArrayThing[i] || depthArrayThing[thisIsVParam]);
		if (ifCondition) {
			resultThing = maxi;
			goto newRet;
		}
		i = uu;
		loopCondition = i >= 0;
		while (loopCondition) {
			ifCondition = depthArrayThing[thisIsUParam] - (1 << i) >= depthArrayThing[LCA];
			if (ifCondition) {
				maxi = max(maxi, RMQMan[thisIsUParam][i]);
				thisIsUParam = P[thisIsUParam][i];
			}

			i = i - 1;
			loopCondition = i >= 0;
		}
		i = uv;
		loopCondition = i >= 0;
		while (loopCondition) {
			ifCondition = depthArrayThing[thisIsVParam] - (1 << i) >= depthArrayThing[LCA];
			if (ifCondition) {
				maxi = max(maxi, RMQMan[thisIsVParam][i]);
				thisIsVParam = P[thisIsVParam][i];
			}

			i = i - 1;
			loopCondition = i >= 0;
		}
		resultThing = maxi;
		goto newRet;
	newRet:
		int queryResult = resultThing;

		printf("%d\n", queryResult);
	}
	return 0;
}
