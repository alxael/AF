#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>> &adjancencyMatrix, vector<bool> &visited, vector<int> &answer)
{
    visited[node] = true;
    for (auto nextNode : adjancencyMatrix[node])
        if (!visited[nextNode])
            dfs(nextNode, adjancencyMatrix, visited, answer);
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

void directedAcyclicGraph(int nodeCount, vector<vector<int>> &adjancencyMatrix, vector<int> &topologicalOrder, vector<int> &answer, vector<int> &predecessor)
{
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
    {
        answer[nodeIndex] = 0;
        predecessor[nodeIndex] = nodeIndex;
    }

    for (auto node : topologicalOrder)
        for (auto nextNode : adjancencyMatrix[node])
            if (answer[node] + 1 > answer[nextNode])
            {
                answer[nextNode] = answer[node] + 1;
                predecessor[nextNode] = node;
            }
}

int main()
{
    int nodeCount, vertexCount, endNodeCount, source, destination, endNode;
    cin >> nodeCount >> vertexCount >> endNodeCount;

    vector<vector<int>> adjancencyMatrix(nodeCount + 1);
    vector<int> topologicalOrder(nodeCount), answer(nodeCount + 1), predecessor(nodeCount + 1), endNodes(endNodeCount);

    for (int endNodeIndex = 1; endNodeIndex <= endNodeCount; endNodeIndex++)
    {
        cin >> endNode;
        endNodes.push_back(endNode);
    }

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        cin >> source >> destination;
        adjancencyMatrix[source].push_back(destination);
    }

    topologicalSort(nodeCount, adjancencyMatrix, topologicalOrder);
    directedAcyclicGraph(nodeCount, adjancencyMatrix, topologicalOrder, answer, predecessor);

    int maxChainLength = 0, maxChainEnd = 0;
    for (auto endNode : endNodes)
        if (answer[endNode] > maxChainLength)
        {
            maxChainLength = answer[endNode];
            maxChainEnd = endNode;
        }

    vector<int> maxChain{maxChainEnd};
    int currentNode = maxChainEnd;
    while (predecessor[currentNode] != currentNode)
    {
        maxChain.push_back(predecessor[currentNode]);
        currentNode = predecessor[currentNode];
    }
    reverse(maxChain.begin(), maxChain.end());

    cout << maxChainLength << '\n';
    for (auto node : maxChain)
        cout << node << ' ';
    return 0;
}