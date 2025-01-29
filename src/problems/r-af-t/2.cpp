#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

void dfs(int node, int connectedComponentIndex, int nodeCount, vector<vector<int>> &adjacencyList, vector<bool> &visited, vector<int> &connectedComponents)
{
    visited[node] = true;
    connectedComponents[node] = connectedComponentIndex;

    for (auto nextNode : adjacencyList[node])
        if (!visited[nextNode])
            dfs(nextNode, connectedComponentIndex, nodeCount, adjacencyList, visited, connectedComponents);

    for(auto nextNode : adjacencyList[node])
        connectedComponents[node] = min(connectedComponents[node], connectedComponents[nextNode]);
}

void connectedComponents(int nodeCount, vector<vector<int>> &adjacencyList, vector<int> &connectedComponents)
{
    vector<bool> visited(nodeCount + 1, false);
    int connectedComponentIndex = 0;
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (connectedComponents[nodeIndex] == 0)
        {
            connectedComponentIndex++;
            dfs(nodeIndex, connectedComponentIndex, nodeCount, adjacencyList, visited, connectedComponents);
        }
}

int main()
{
    ifstream in("test.in");
    ofstream out("test.out");

    bool answer;
    int nodeCount, vertexCount, queryCount, source, destination, cost;
    in >> nodeCount >> vertexCount;

    vector<vector<int>> adjacencyListOne(nodeCount + 1), adjacencyListTwo(nodeCount + 1);
    vector<int> connectedComponentsOne(nodeCount + 1, 0), connectedComponentsTwo(nodeCount + 1, 0);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination >> cost;
        if (cost == 0)
        {
            adjacencyListOne[source].push_back(destination);
            adjacencyListOne[destination].push_back(source);
        }
        else
        {
            adjacencyListTwo[source].push_back(destination);
            adjacencyListTwo[destination].push_back(source);
        }
    }

    connectedComponents(nodeCount, adjacencyListOne, connectedComponentsOne);
    connectedComponents(nodeCount, adjacencyListTwo, connectedComponentsTwo);

    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
    {
        cout << nodeIndex << ": " << connectedComponentsOne[nodeIndex] << '\n';
    }
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
    {
        cout << nodeIndex << ": " << connectedComponentsTwo[nodeIndex] << '\n';
    }

    in >> queryCount;
    for (int queryIndex = 1; queryIndex <= queryCount; queryIndex++)
    {
        in >> source >> destination >> cost;
        if (cost == 0)
            answer = (connectedComponentsOne[source] == connectedComponentsOne[destination]);
        else
            answer = (connectedComponentsTwo[source] == connectedComponentsTwo[destination]);
        out << (answer ? "DA" : "NU") << '\n';
    }

    return 0;
}