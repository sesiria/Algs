// C++ program for implementation of Edmonds-Karp Algorithm
#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
// number of vertices in given graph
#define V 6

// Comparator for pair
struct cmp
{
    bool operator()(const pair<int, int> &l, const pair<int, int> &r)
    {
        return l.second > r.second;
    }
};
/**
 * short path algorithm implementation by Dijkstra algorithm via priority_queue
 * s is the source
 * t is the sink
 * parent[] is the shortest path from s to t
 */
bool bfsDj(int rGraph[V][V], int s, int t, int parent[])
{
    vector<bool> visited(V, false);
    vector<int> Keys(V, INT_MAX);
    Keys[s] = 0; // init the start point as 0.
    parent[s] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> minHeap;

    // we can use the adjacent map table for quick search.
    minHeap.push(make_pair(s, Keys[s]));

    while(!minHeap.empty()) {
        auto u = minHeap.top().first;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = true;
        // iterate for each adjacent.
        // we can use the adjacent map table for quick search.
        for(int v = 0; v < V; ++v) {
            int weight = rGraph[u][v];
            if(weight > 0 && Keys[u] + weight < Keys[v]) {
                Keys[v] = Keys[u] + weight;
                parent[v] = u;
                minHeap.push(make_pair(v, Keys[v]));
            }
        }
    }
    return visited[t] == true;
}

// Returns the maximum flow from s to t in the given graph
int edmonds_Karp(int graph[V][V], int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates
                      // residual capacity of edge from i to j (if there
                      // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // This array is filled by BFS and to store path

    int max_flow = 0; // There is no flow initially

    // Augment the flow while tere is path from source to sink
    while (bfsDj(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    int graph[V][V] = {{0, 16, 13, 0, 0, 0},
                       {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},
                       {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},
                       {0, 0, 0, 0, 0, 0}};

    cout << "The maximum possible flow is " << edmonds_Karp(graph, 0, 5);

    return 0;
}