#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

void bfs(int nodeCount, int startNode, int endNode, vector<vector<int>> &adjacencyMatrix, vector<vector<int>> &adjancencyList, vector<int> &path)
{
    vector<int> visited(nodeCount + 1, false), predecessor(nodeCount + 1, 0);
    queue<int> nodes;
    bool found = false;

    path.clear();
    nodes.push(startNode);
    visited[startNode] = true;

    while (!nodes.empty() && !found)
    {
        int node = nodes.front();
        nodes.pop();

        for (auto destination : adjancencyList[node])
            if (!visited[destination] && adjacencyMatrix[node][destination])
            {
                predecessor[destination] = node;
                if (destination == endNode)
                {
                    found = true;
                    break;
                }
                visited[destination] = true;
                nodes.push(destination);
            }
    }

    if (found)
    {
        int currentNode = endNode;
        while (predecessor[currentNode])
        {
            path.push_back(currentNode);
            currentNode = predecessor[currentNode];
        }
        path.push_back(startNode);
        reverse(path.begin(), path.end());
    }
}

int edmondsKarp(int nodeCount, int startNode, int endNode, vector<vector<pair<int, int>>> &adjacencyList)
{
    vector<vector<int>> residualAdjacencyMatrix(nodeCount + 1, vector<int>(nodeCount + 1, 0)), processedAdjacencyList(nodeCount + 1);

    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        for (auto vertex : adjacencyList[nodeIndex])
        {
            residualAdjacencyMatrix[nodeIndex][vertex.first] = vertex.second;
            processedAdjacencyList[nodeIndex].push_back(vertex.first);
            processedAdjacencyList[vertex.first].push_back(nodeIndex);
        }

    vector<int> path;
    int maxFlow = 0;
    while (true)
    {
        path.clear();
        bfs(nodeCount, startNode, endNode, residualAdjacencyMatrix, processedAdjacencyList, path);
        if (path.empty())
            break;

        int pathMinimum = numeric_limits<int>::max();
        for (int pathIndex = 1; pathIndex < path.size(); pathIndex++)
        {
            int source = path[pathIndex - 1];
            int destination = path[pathIndex];
            pathMinimum = min(pathMinimum, residualAdjacencyMatrix[source][destination]);
        }

        for (int pathIndex = 1; pathIndex < path.size(); pathIndex++)
        {
            int source = path[pathIndex - 1];
            int destination = path[pathIndex];
            residualAdjacencyMatrix[source][destination] -= pathMinimum;
            residualAdjacencyMatrix[destination][source] += pathMinimum;
        }

        maxFlow += pathMinimum;
    }

    return maxFlow;
}

int main()
{
    int nodeCount, vertexCount, source, destination;
    cin >> nodeCount >> vertexCount;

    vector<vector<pair<int, int>>> adjacencyList(nodeCount + 1);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        cin >> source >> destination;
        adjacencyList[source].push_back({destination, 1});
    }

    int maxFlow = edmondsKarp(nodeCount, 1, nodeCount, adjacencyList);
    cout << maxFlow;
    return 0;
}