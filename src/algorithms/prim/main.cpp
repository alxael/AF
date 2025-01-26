#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

void prim(int nodeCount, vector<tuple<int, int, int>> &vertices, vector<tuple<int, int, int>> &answerVertices, int startNode = 1)
{
    vector<vector<pair<int, int>>> adjancencyMatrix(nodeCount + 1);
    for (auto [source, destination, weight] : vertices)
    {
        adjancencyMatrix[source].push_back({weight, destination});
        adjancencyMatrix[destination].push_back({weight, source});
    }

    vector<bool> visited(nodeCount + 1, false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minimumVertices;

    minimumVertices.push({0, 0, startNode});
    while (!minimumVertices.empty())
    {
        auto [weight, source, destination] = minimumVertices.top();
        minimumVertices.pop();

        if (visited[destination])
            continue;

        if (destination != startNode)
            answerVertices.push_back({source, destination, weight});
        visited[destination] = true;

        for (auto [vertexWeight, vertexDestination] : adjancencyMatrix[destination])
            if (!visited[vertexDestination])
                minimumVertices.push({vertexWeight, destination, vertexDestination});
    }
}

int main()
{
    ifstream in("apm.in");
    ofstream out("apm.out");

    int nodeCount, vertexCount, source, destination, weight;
    in >> nodeCount >> vertexCount;

    vector<tuple<int, int, int>> vertices, answerVertices;
    vertices.reserve(vertexCount);

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination >> weight;
        vertices.push_back(tuple<int, int, int>(source, destination, weight));
    }

    prim(nodeCount, vertices, answerVertices);

    int vertexWeights = 0;
    for (auto vertex : answerVertices)
        vertexWeights += get<2>(vertex);

    out << vertexWeights << '\n';
    out << answerVertices.size() << '\n';
    for (auto [source, destination, weight] : answerVertices)
        out << source << ' ' << destination << '\n';

    return 0;
}