#include <iostream>
#include <vector>

using namespace std;

struct Tuple {
	Tuple(int s, int f) {
		this->s = s;
		this->f = f;
	}

	int s, f;
};

void print(Tuple t) {
	cout << "(" << t.s << ", " << t.f << ")";
}

// can be optimized
bool overlap(Tuple t1, Tuple t2) {
	int s1 = t1.s, f1 = t1.f, s2 = t2.s, f2 = t2.f;
	return ((s1 <= s2) && (s2 <= f1) && (f1 <= f2)) || ((s2 <= s1) && (s1 <= f2) && (f2 <= f1));
}

int length(Tuple t) {
	return t.f - t.s + 1;
}

int length(Tuple t1, Tuple t2) {
	return (t1.f - t1.s + 1) + (t2.f - t2.s + 1);
}

int main() {
	int N, K;

	cin >> N >> K;

	int p[N];

	for (int i = 0; i < N; i++) {
		cin >> p[i];
	}

	vector<Tuple> *a = new vector<Tuple>[K + 1]; // holds which tuples have sum equal to v[i]

	for (int i = 0; i < N; i++) {
		int sum = 0; // prefix sum
		for (int j = i; j < N; j++) {
			sum += p[j];
			if (sum <= K) {
				a[sum].push_back(Tuple(i, j));
			}
			else {
				break;
			}
		}
	}

	// for (int i = 0; i < K + 1; i++) {

	// 	for (Tuple t : a[i]) {
	// 		print(t); cout << " ";
	// 	}
	// 	cout << endl;
	// }

	int minimum = N + 1;

	for (int i = 0; i < (K + 1) / 2; i++) { // is it really (K + 1) / 2?
		if (a[i].size() == 0)
			continue;
		for (Tuple t1 : a[i]) {
			int sum = i;
			int comp = K - sum; // complementary sum
			for (Tuple t2 : a[comp]) {
				if (!overlap(t1, t2)) {
					int Length = length(t1, t2);
					if (Length < minimum) {
						minimum = Length;
					}
					// print(t1); cout << " "; print(t2); cout << " ";
					// cout << " --> " << length(t1, t2) << endl;
				}
			}
		}
	}
	// Special case for i = K
	for (Tuple t : a[K]) {
		int Length = length(t);
		if (Length < minimum) {
			minimum = Length;
		}
		// cout << "(" << t.s << ", " << t.f << ")"
		//      << " --> " << length(t) << endl;
	}

	cout << (minimum == N + 1 ? -1 : minimum) << endl;

	// for (int i = 0; i < K + 1; i++) {
	// 	cout << a[i].size() << endl;
	// }
	delete[] a;
}
