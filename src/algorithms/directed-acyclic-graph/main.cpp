#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

void dfs(int node, vector<vector<pair<int, int>>> &adjancencyMatrix, vector<bool> &visited, vector<int> &answer)
{
    visited[node] = true;
    for (auto vertex : adjancencyMatrix[node])
        if (!visited[vertex.first])
            dfs(vertex.first, adjancencyMatrix, visited, answer);
    answer.push_back(node);
}

void topologicalSort(int nodeCount, vector<vector<pair<int, int>>> &adjancencyMatrix, vector<int> &answer)
{
    vector<bool> visited(nodeCount + 1, false);
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (!visited[nodeIndex])
            dfs(nodeIndex, adjancencyMatrix, visited, answer);

    reverse(answer.begin(), answer.end());
}

void directedAcyclicGraph(int startNode, int nodeCount, vector<vector<pair<int, int>>> &adjancencyMatrix, vector<int> &topologicalOrder, vector<int> &answer)
{
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        answer[nodeIndex] = (numeric_limits<int>::max() >> 1);
    answer[startNode] = 0;

    for (auto node : topologicalOrder)
        if (answer[node] != (numeric_limits<int>::max() >> 1))
            for (auto vertex : adjancencyMatrix[node])
                answer[vertex.first] = min(answer[vertex.first], answer[node] + vertex.second);
}

int main()
{
    ifstream in("dag.in");
    ofstream out("dag.out");

    int nodeCount, vertexCount, source, destination, weight;
    in >> nodeCount >> vertexCount;

    vector<vector<pair<int, int>>> adjancencyMatrix(nodeCount + 1);
    vector<int> topologicalOrder(nodeCount), answer(nodeCount + 1);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination >> weight;
        adjancencyMatrix[source].push_back({destination, weight});
    }

    topologicalSort(nodeCount, adjancencyMatrix, topologicalOrder);
    directedAcyclicGraph(1, nodeCount, adjancencyMatrix, topologicalOrder, answer);

    for (int nodeIndex = 2; nodeIndex <= nodeCount; nodeIndex++)
        out << ((answer[nodeIndex] == (numeric_limits<int>::max() >> 1)) ? 0 : answer[nodeIndex]) << ' ';

    return 0;
}