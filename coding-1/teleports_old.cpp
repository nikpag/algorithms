// #include <algorithm>
// #include <fstream>
// #include <iostream>

// using namespace std;

// TODO: Use constant references wherever possible in order to speedup things

// struct Portal {
// 	int a;
// 	int b;
// 	int w;
// };

// bool portalComparison(Portal p1, Portal p2) {
// 	return p1.w < p2.w;
// }

// int main() {
// 	int answer = 0;

// 	// int N, M;
// 	// cin >> N >> M;

// 	int c[N];
// 	Portal p[M];

// 	for (int i = 0; i < N; i++) {
// 		cin >> c[i];
// 	}

// 	for (int j = 0; j < M; j++) {
// 		cin >> p[j].a >> p[j].b >> p[j].w;
// 	}

// 	sort(p, p + M, portalComparison);

// 	for (int i = 0; i < M; i++) {
// 		cout << p[i].a << " " << p[i].b << " " << p[i].w << endl;
// 	}
// }
