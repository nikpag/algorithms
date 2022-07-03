#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<vector<int>> a;
	a.resize(3);

	for (int i = 0; i < 3; i++) {
		a[i].resize(3);
		cout << "I have been called" << endl;
	}

	for (auto item1 : a) {
		for (auto item2 : item1) {
			cout << "I also have been called" << endl;
			cout << item2 << endl;
		}
	}

	cout << a[0].size() << endl;
}
