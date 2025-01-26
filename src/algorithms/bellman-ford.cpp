#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

void bellmanFord(int startNode, int nodeCount, vector<vector<pair<int, int>>> costMatrix, vector<int> &answer, vector<int> &predecessor, vector<int> &cycle)
{
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
    {
        answer[nodeIndex] = numeric_limits<int>::max() / 2;
        predecessor[nodeIndex] = 0;
    }

    answer[startNode] = 0;
    for (int nodeIndex = 1; nodeIndex < nodeCount - 1; nodeIndex++)
    {
        bool isAnythingUpdated = false;
        for (int sourceNodeIndex = 1; sourceNodeIndex <= nodeCount; sourceNodeIndex++)
            for (auto itDestination = costMatrix[sourceNodeIndex].begin(); itDestination != costMatrix[sourceNodeIndex].end(); itDestination++)
                if (answer[sourceNodeIndex] + itDestination->second < answer[itDestination->first])
                {
                    answer[itDestination->first] = answer[sourceNodeIndex] + itDestination->second;
                    predecessor[itDestination->first] = sourceNodeIndex;
                    isAnythingUpdated = true;
                }
        if (!isAnythingUpdated)
            break;
    }

    for (int sourceNodeIndex = 1; sourceNodeIndex <= nodeCount; sourceNodeIndex++)
        for (auto itDestination = costMatrix[sourceNodeIndex].begin(); itDestination != costMatrix[sourceNodeIndex].end(); itDestination++)
            if (answer[sourceNodeIndex] + itDestination->second < answer[itDestination->first])
            {
                answer[itDestination->first] = answer[sourceNodeIndex] + itDestination->second;

                vector<bool> visited(nodeCount + 1, false);
                visited[sourceNodeIndex] = true;

                int currentNode = itDestination->first;
                while (!visited[currentNode])
                {
                    visited[currentNode] = true;
                    currentNode = predecessor[currentNode];
                }

                cycle.clear();

                cycle.push_back(currentNode);
                sourceNodeIndex = predecessor[currentNode];
                while (sourceNodeIndex != currentNode)
                {
                    cycle.push_back(sourceNodeIndex);
                    sourceNodeIndex = predecessor[sourceNodeIndex];
                }

                return;
            }
}

int main()
{
    ifstream in("bellmanford.in");
    ofstream out("bellmanford.out");

    int nodeCount, vertexCount, source, destination, cost;
    in >> nodeCount >> vertexCount;

    vector<vector<pair<int, int>>> costMatrix(nodeCount + 1);
    vector<int> answer(nodeCount + 1, numeric_limits<int>::max() / 2), predecessor(nodeCount + 1, 0), cycle;

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination >> cost;
        costMatrix[source].push_back(pair<int, int>(destination, cost));
    }

    bellmanFord(1, nodeCount, costMatrix, answer, predecessor, cycle);

    if (!cycle.empty())
    {
        out << "Ciclu negativ!";
        return 0;
    }

    for (int nodeIndex = 2; nodeIndex < answer.size(); nodeIndex++)
        out << ((answer[nodeIndex] == numeric_limits<int>::max() / 2) ? 0 : answer[nodeIndex]) << ' ';

    return 0;
}