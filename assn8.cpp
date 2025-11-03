#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
struct Node {
vector<int> path;
vector<int> visited;

int cost;
int bound;
int level;
};
int N;
vector<vector<int>> costMatrix;
// Calculate lower bound
int calcBound(const Node& node) {
int bound = node.cost;
for (int i = 0; i < N; ++i) {
if (!node.visited[i]) {
int minEdge = INT_MAX;
for (int j = 0; j < N; ++j) {
if (i != j && costMatrix[i][j] != INT_MAX)
minEdge = min(minEdge, costMatrix[i][j]);
}
if (minEdge != INT_MAX)
bound += minEdge;
}
}
return bound;
}
struct Compare {
bool operator()(const Node& a, const Node& b) {
return a.bound > b.bound; // Min-heap based on bound
}
};

vector<int> tspLCBranchBound(int start) {
priority_queue<Node, vector<Node>, Compare> pq;
Node root;
root.path.push_back(start);
root.visited = vector<int>(N, 0);
root.visited[start] = 1;
root.cost = 0;
root.level = 1;
root.bound = calcBound(root);
pq.push(root);
int minCost = INT_MAX;
vector<int> bestPath;
while (!pq.empty()) {
Node curr = pq.top();
pq.pop();
if (curr.bound >= minCost) continue;
if (curr.level == N) {
int last = curr.path.back();
if (costMatrix[last][start] == INT_MAX) continue;
int totalCost = curr.cost + costMatrix[last][start];
if (totalCost < minCost) {
minCost = totalCost;
bestPath = curr.path;
bestPath.push_back(start);
}
continue;
}

int prev = curr.path.back();
for (int next = 0; next < N; ++next) {
if (!curr.visited[next] && costMatrix[prev][next] != INT_MAX) {
Node child = curr;
child.path.push_back(next);
child.visited[next] = 1;
child.level++;
child.cost = curr.cost + costMatrix[prev][next];
child.bound = calcBound(child);
if (child.bound < minCost)
pq.push(child);
}
}
}
cout << "Minimum Cost: " << minCost << endl;
return bestPath;
}
int main() {
cout << "Enter number of cities: ";
cin >> N;
costMatrix.assign(N, vector<int>(N));
cout << "Enter cost matrix (" << N << "x" << N << "):\n";
for (int i = 0; i < N; ++i)
for (int j = 0; j < N; ++j)
cin >> costMatrix[i][j];
vector<int> route = tspLCBranchBound(0);

cout << "Optimal Route: ";

for (int city : route)
cout << city << " ";
cout << endl;
return 0;
}
