#include <iostream>
#include <string>

using namespace std;

int main() {
    int N, M;

    cin >> N >> M;

    string *xy = new string[M];
    int *A = new int[M];
    int *P = new int[M];

    for (int i = 0; i < M; i++) {
        cin >> xy[i] >> A[i] >> P[i];
    }
}
