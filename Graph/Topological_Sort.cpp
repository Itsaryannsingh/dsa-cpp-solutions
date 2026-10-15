#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void topologicalSort(int vertices,
                     vector<vector<int>>& graph)
{
    vector<int> indegree(vertices, 0);

    // Calculate indegree of every vertex
    for (int u = 0; u < vertices; u++)
    {
        for (int v : graph[u])
        {
            indegree[v]++;
        }
    }

    queue<int> q;

    // Add vertices with indegree 0
    for (int i = 0; i < vertices; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        order.push_back(current);

        for (int neighbour : graph[current])
        {
            indegree[neighbour]--;

            if (indegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }

    // If not all vertices were processed, a cycle exists
    if (order.size() != vertices)
    {
        cout << "Topological sorting is not possible."
             << endl;
        cout << "The graph contains a directed cycle."
             << endl;
        return;
    }

    cout << "Topological Order: ";

    for (int vertex : order)
    {
        cout << vertex << " ";
    }

    cout << endl;
}

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of directed edges: ";
    cin >> edges;

    vector<vector<int>> graph(vertices);

    cout << "Enter edges (u v) representing u -> v:\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
    }

    topologicalSort(vertices, graph);

    return 0;
}
