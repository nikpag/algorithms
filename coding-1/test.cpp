#include <iostream>
using namespace std;

void change(int a[]) {
	for (int i = 0; i < 5; i++) {
		a[i] = 1;
	}
}

void changeDeeper(int a[]) {
	change(a);
}

int main() {
	int a[] = {1, 2, 3, 4, 5};

	changeDeeper(a);

	for (int i = 0; i < 5; i++) {
		cout << a[i] << " ";
	}

	cout << endl;
}
