#include <bits/stdc++.h>
using namespace std;
struct Edge {int to, w;};
vector<int> dijkstra(int s, vector<vector<Edge>>& g) {
int V = g.size();
vector<int> d(V, INT_MAX);
d[s] = 0;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
pq.push({0, s});
while(!pq.empty()) {
auto [dist, u] = pq.top(); pq.pop();
if(dist > d[u]) continue;
for(auto& e : g[u]) {
if(d[e.to] > d[u] + e.w) {
d[e.to] = d[u] + e.w;
pq.push({d[e.to], e.to});
}
}
}

return d;
}
int main() {
int V, E;
cout << "Enter number of intersections (vertices): ";
cin >> V;
cout << "Enter number of roads (edges): ";
cin >> E;
vector<vector<Edge>> g(V);
cout << "Enter edges (u v w):\n";
for(int i = 0, u, v, w; i < E; i++) {
cin >> u >> v >> w;
g[u].push_back({v, w});
g[v].push_back({u, w});
}
int s; cout << "Enter ambulance start location (source): ";
cin >> s;
int H; cout << "Enter number of hospitals: ";
cin >> H;
vector<int> h(H);
cout << "Enter hospital nodes: ";
for(int i = 0; i < H; i++) cin >> h[i];
auto d = dijkstra(s, g);
int minT = INT_MAX, nearest = -1;
for(int x : h) if(d[x] < minT) minT = d[x], nearest = x;
if(nearest == -1) cout << "No hospital reachable.\n";
else cout << "Nearest hospital is at node " << nearest << " with travel time " << minT << "
minutes.\n";
}
