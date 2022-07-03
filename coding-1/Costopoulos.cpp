#include <algorithm> //sort
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
int N, M;
int subgraph_num = 0;
// int belongs_to_subgraph[M];
struct portal {
	int a, b, w;
};

void addEdge(vector<int> adj[], int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

/*void printGraph(vector<int> adj[], int V)
{
    for (int v = 1; v < V; ++v)
    {
	cout << "\n Adjacency list of vertex "
	    << v << "\n head ";
	for (auto x : adj[v])
	    cout << "-> " << x;
	printf("\n");
    }
}*/

void DFSUtil2(int v, vector<int> adj[], bool visited[], int belongs[]) {

	// belongs[v] = subgraph_num;
	vector<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			visited[*i] = true;
			// subgraph_num++;
			belongs[*i] = subgraph_num;
			DFSUtil2(*i, adj, visited, belongs);
		}
	}
}

bool regarding_width(portal p1, portal p2) {
	return (p1.w < p2.w);
}

int binsearch(portal p[], int l, int r, int belongs_to_sub[], int carray[]) {
	int solution;
	bool isconnected;
	// subgraph_num = 1;
	int m;
	while (l <= r) {
		isconnected = true;
		int templeft = l;
		subgraph_num = 1;
		// int solution;
		m = l + (r - l) / 2;
		vector<int> adj[N + 1];
		for (int i = 1; i < M + 1; i++) {
			if (p[i].w >= p[m].w) { // create graph for portals >= binsearch selected portal
				addEdge(adj, p[i].a, p[i].b);
			}
		}
		// bool* visited = new bool[N + 1];
		bool visited[N + 1];
		for (int i = 1; i < N + 1; i++) {
			belongs_to_sub[i] = 0;
			visited[i] = false;
		}

		for (int i = 1; i < N + 1; i++) {
			if (!visited[i]) {
				subgraph_num++;
				visited[i] = true;
				belongs_to_sub[i] = subgraph_num;
				DFSUtil2(i, adj, visited, belongs_to_sub);
			}
		}

		for (int i = 1; i < N + 1; i++) {
			if (belongs_to_sub[carray[i]] == belongs_to_sub[i]) {

				solution = p[m].w;
				l = m + 1;
				continue;
			}
			else {
				isconnected = false;
				r = m - 1;
				l = templeft;
				break;
			}
		}
	}
	// cout << "Sol is " << solution;
	if (!isconnected) {
		return p[m - 1].w;
	}
	else
		return solution;
}

int main() {
	// int N, M;
	// int M;
	// cin >> N >> M;
	scanf("%d %d", &N, &M);
	int c[N + 1]; /*, a[M+1], b[M+1], w[M+1]*/ // c -> universes, a, b -> unified universes, w -> width
	portal portalarray[M + 1];
	int belongs_to_subgraph[N + 1];
	for (int i = 1; i < N + 1; i++) {
		// cin >> c[i];
		scanf("%d", &c[i]);
	}
	for (int i = 1; i < M + 1; i++) {
		// cin >> portalarray[i].a >> portalarray[i].b >> portalarray[i].w;
		scanf("%d %d %d", &portalarray[i].a, &portalarray[i].b, &portalarray[i].w);
	}
	sort(portalarray + 1, portalarray + M + 1, regarding_width);
	/*for (int i = 1; i <=10 ; i++)
	{
	    cout << portalarray[i].w << endl;
	}*/
	/*for (int i = 1; i < N + 1; i++)
	{
	    belongs_to_subgraph[i] = 0;
	}*/
	int result = binsearch(portalarray, 1, M, belongs_to_subgraph, c);
	// cout << result << endl;
	printf("%d\n", result);
}
