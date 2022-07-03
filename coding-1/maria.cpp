#include <fstream>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

struct elem {
	int val, len;
};

int N, K;
int main(int argc, char *argv[]) {

	ifstream fd;
	fd.open(argv[1], ios::in);
	map<int, int> ExiS;
	fd >> N >> K;
	int *A = new int[N];
	bool *Aq1 = new bool[N];
	elem *Aq = new elem[N];
	int best = -1;
	//queue<elem>* Aq = new queue<elem>[N];
	for (int i = 0; i < N; ++i)
		fd >> A[i];
	for (int i = 0; i < N; ++i) {
		if (A[i] == K)
			best = 1;
		if (A[i] < K) {
			Aq[i] = {A[i], 1};
			Aq1[i] = true;
		}
	}
	ExiS[0] = 0;
	int lim = 0;
	int temp, j;
	//queue<elem> curr;
	elem tem;
	while (lim < N) {
		for (int i = 0; i <= lim; ++i) {
			if (Aq1[i]) {
				tem = Aq[i];
				if (ExiS.find(tem.val) == ExiS.end())
					ExiS[tem.val] = tem.len;
				else if (tem.len < ExiS[tem.val])
					ExiS[tem.val] = tem.len;
				Aq1[i] = false;
				//cout << "new ** " << A[lim+1] << endl;
				if (lim < N - 1 && tem.val + A[lim + 1] <= K) {
					Aq1[i] = true;
					Aq[i] = {tem.val + A[lim + 1], tem.len + 1};
				}

				//curr.push(tem);
			}
		}
		temp = A[lim];
		j = lim + 1;
		if (temp == K)
			best = 1;
		while (temp <= K && j < N) {
			temp += A[j];
			if (ExiS.find(K - temp) != ExiS.end() && (best == -1 or ExiS[K - temp] + j - lim + 1 < best))
				best = ExiS[K - temp] + j - lim + 1;
			j++;
		}

		//cout << "curr ----------" << endl;
		/*
		while(!curr.empty()){
			tem = curr.front();
			//cout << "*" << tem.val << endl;
			curr.pop();
			if(ExiS.find(tem.val) == ExiS.end()) ExiS[tem.val] = tem.len;
			else if (tem.len < ExiS[tem.val]) ExiS[tem.val] = tem.len;
		}
		*/
		lim++;
	}
	cout << best << endl;
	fd.close();
}
