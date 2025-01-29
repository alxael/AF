#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include <limits>

using namespace std;

void dijkstra(int startNode, vector<pair<int, int>> costMatrix[], vector<bool> &visited, vector<int> &answer)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nodes;
    nodes.push(pair<int, int>(0, startNode));

    answer[startNode] = 0;
    while (!nodes.empty())
    {
        pair<int, int> node = nodes.top();
        nodes.pop();

        for (auto it = costMatrix[node.second].begin(); it != costMatrix[node.second].end(); it++)
            if (!visited[it->first])
            {
                answer[it->first] = min(answer[it->first], answer[node.second] + it->second);
                nodes.push(pair<int, int>(answer[it->first], it->first));
            }

        visited[node.second] = true;
    }
}

int main()
{
    int nodeCount, vertexCount, source, destination, cost;
    cin >> nodeCount >> vertexCount;

    vector<pair<int, int>> costMatrix[nodeCount + 1];
    vector<bool> visited(nodeCount + 1, false);
    vector<int> answer(nodeCount + 1, numeric_limits<int>::max() >> 1);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        cin >> source >> destination >> cost;
        costMatrix[source].push_back({destination, cost});
    }

    dijkstra(1, costMatrix, visited, answer);

    int maxDistance = 0;
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        maxDistance = max(maxDistance, answer[nodeIndex]);

    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if(maxDistance == answer[nodeIndex])
            cout << nodeIndex << ' ';

    return 0;
}