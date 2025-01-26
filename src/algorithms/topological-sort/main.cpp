#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>> &adjancencyMatrix, vector<bool> &visited, vector<int> &answer)
{
    visited[node] = true;
    for (auto destination : adjancencyMatrix[node])
        if (!visited[destination])
            dfs(destination, adjancencyMatrix, visited, answer);
    answer.push_back(node);
}

void topologicalSort(int nodeCount, vector<vector<int>> &adjancencyMatrix, vector<int> &answer)
{
    vector<bool> visited(nodeCount + 1, false);
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (!visited[nodeIndex])
            dfs(nodeIndex, adjancencyMatrix, visited, answer);

    reverse(answer.begin(), answer.end());
}

int main()
{
    ifstream in("sortaret.in");
    ofstream out("sortaret.out");

    int nodeCount, vertexCount, source, destination;
    in >> nodeCount >> vertexCount;

    vector<vector<int>> adjancencyMatrix(nodeCount + 1, vector<int>());
    vector<int> answer(nodeCount);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination;
        adjancencyMatrix[source].push_back(destination);
    }

    topologicalSort(nodeCount, adjancencyMatrix, answer);

    for (auto node : answer)
        out << node << ' ';
    return 0;
}