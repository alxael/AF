#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void dfs(int node, vector<vector<int>> &adjacencyList, vector<bool> &visited, vector<int> &predecessor)
{
    visited[node] = true;

    for (auto nextNode : adjacencyList[node])
        if (!visited[nextNode])
        {
            predecessor[nextNode] = node;
            dfs(nextNode, adjacencyList, visited, predecessor);
        }
}

void getAdjacencyListFromPredecessor(int nodeCount, vector<int> &predecessor, vector<vector<int>> &tree)
{
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (predecessor[nodeIndex])
        {
            tree[nodeIndex].push_back(predecessor[nodeIndex]);
            tree[predecessor[nodeIndex]].push_back(nodeIndex);
        }
}

void printAdjacencyList(int nodeCount, vector<vector<int>> &adjacencyList)
{
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
    {
        for (auto nextNode : adjacencyList[nodeIndex])
            cout << nextNode << ' ';
        cout << '\n';
    }
}

int main()
{
    int nodeCount, vertexCount, source, destination;
    cin >> nodeCount >> vertexCount;

    vector<vector<int>> adjacencyList(nodeCount + 1);
    vector<bool> visited(nodeCount + 1);
    vector<int> predecessorFirst(nodeCount + 1), predecessorSecond(nodeCount + 1);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        cin >> source >> destination;
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }

    fill(visited.begin(), visited.end(), false);
    dfs(1, adjacencyList, visited, predecessorFirst);

    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (!visited[nodeIndex])
        {
            cout << "Nu";
            return 0;
        }

    fill(visited.begin(), visited.end(), false);
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        reverse(adjacencyList[nodeIndex].begin(), adjacencyList[nodeIndex].end());
    dfs(1, adjacencyList, visited, predecessorSecond);

    bool different = false;
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (predecessorFirst[nodeIndex] != predecessorSecond[nodeIndex])
        {
            different = true;
            break;
        }
    if (!different)
    {
        cout << "Nu";
        return 0;
    }

    vector<vector<int>> treeFirst(nodeCount + 1), treeSecond(nodeCount + 1);
    getAdjacencyListFromPredecessor(nodeCount, predecessorFirst, treeFirst);
    getAdjacencyListFromPredecessor(nodeCount, predecessorSecond, treeSecond);

    cout << "Da" << '\n';
    printAdjacencyList(nodeCount, treeFirst);
    printAdjacencyList(nodeCount, treeSecond);
    return 0;
}