#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

void dijkstra(int startNode, vector<vector<pair<int, int>>> &costMatrix, vector<bool> &visited, vector<int> &answer)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nodes;
    nodes.push(pair<int, int>(0, startNode));

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
    ifstream in("dijkstra.in");
    ofstream out("dijkstra.out");

    int nodeCount, vertexCount, source, destination, cost;
    in >> nodeCount >> vertexCount;

    vector<vector<pair<int, int>>> costMatrix(nodeCount + 1, vector<pair<int, int>>());
    vector<bool> visited(nodeCount + 1, false);
    vector<int> answer(nodeCount + 1, numeric_limits<int>::max());

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination >> cost;
        costMatrix[source].push_back(pair<int, int>(destination, cost));
    }

    answer[1] = 0;
    dijkstra(1, costMatrix, visited, answer);

    for (int nodeIndex = 2; nodeIndex < answer.size(); nodeIndex++)
        out << ((answer[nodeIndex] == numeric_limits<int>::max()) ? 0 : answer[nodeIndex]) << ' ';

    return 0;
}