#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>> &adjancencyMatrix, vector<bool> &visited, vector<int> &answer)
{
    visited[node] = true;
    for (auto it = adjancencyMatrix[node].begin(); it != adjancencyMatrix[node].end(); it++)
        if (!visited[*it])
            dfs(*it, adjancencyMatrix, visited, answer);
    answer.push_back(node);
}

int main()
{
    ifstream in("sortaret.in");
    ofstream out("sortaret.out");

    int nodeCount, vertexCount, source, destination;
    in >> nodeCount >> vertexCount;

    vector<vector<int>> adjancencyMatrix(nodeCount + 1, vector<int>());
    vector<bool> visited(nodeCount + 1, false);
    vector<int> answer;
    answer.reserve(nodeCount);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination;
        adjancencyMatrix[source].push_back(destination);
    }

    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (!visited[nodeIndex])
            dfs(nodeIndex, adjancencyMatrix, visited, answer);

    reverse(answer.begin(), answer.end());
    for (auto it = answer.begin(); it != answer.end(); it++)
        out << *it << ' ';
    return 0;
}