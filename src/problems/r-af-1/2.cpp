#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

bool bfs(int nodeCount, vector<vector<pair<int, int>>> &adjacencyList, tuple<int, int, int> &vertex)
{
    vector<bool> visited(nodeCount + 1, false);
    queue<int> nodes;

    visited[get<0>(vertex)] = true;
    nodes.push(get<0>(vertex));

    while (!nodes.empty())
    {
        int currentNode = nodes.front();
        nodes.pop();

        for (auto nextNode : adjacencyList[currentNode])
            if (!visited[nextNode.first] && nextNode.second < get<2>(vertex) &&
                !(currentNode == get<0>(vertex) && nextNode.first == get<1>(vertex)))
            {
                visited[nextNode.first] = true;
                if (nextNode.first == get<1>(vertex))
                    return false;
                nodes.push(nextNode.first);
            }
    }
    return true;
}

int main()
{
    int nodeCount, vertexCount, queryCount, source, destination, weight, query;
    cin >> nodeCount >> vertexCount;

    vector<vector<pair<int, int>>> adjacencyList(nodeCount + 1);
    vector<tuple<int, int, int>> vertices(vertexCount + 1);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        cin >> source >> destination >> weight;
        adjacencyList[source].push_back({destination, weight});
        adjacencyList[destination].push_back({source, weight});
        vertices[vertexIndex] = {source, destination, weight};
    }

    cin >> queryCount;
    for (int queryIndex = 1; queryIndex <= queryCount; queryIndex++)
    {
        cin >> query;
        cout << (bfs(nodeCount, adjacencyList, vertices[query]) ? "Da" : "Nu") << '\n';
    }
    return 0;
}