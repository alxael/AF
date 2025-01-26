#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <tuple>
#include <algorithm>

using namespace std;

class DisjointSets
{
private:
    vector<int> parent;
    vector<int> height;

public:
    DisjointSets(int nodeCount)
    {
        parent = vector<int>(nodeCount + 1);
        height = vector<int>(nodeCount + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int getParent(int node)
    {
        while (parent[node] != node)
            node = parent[node];
        return node;
    }

    bool areInSameSet(int firstNode, int secondNode)
    {
        return getParent(firstNode) == getParent(secondNode);
    }

    void unite(int firstNode, int secondNode)
    {
        firstNode = this->getParent(firstNode);
        secondNode = this->getParent(secondNode);

        if (height[firstNode] <= height[secondNode])
        {
            parent[firstNode] = secondNode;
            height[secondNode]++;
        }
        else
        {
            parent[secondNode] = firstNode;
            height[firstNode]++;
        }
    }
};

bool compare(tuple<int, int, int> first, tuple<int, int, int> second)
{
    return get<2>(first) < get<2>(second);
}

void kruskal(int nodeCount, vector<tuple<int, int, int>> &vertices, vector<tuple<int, int, int>> &answerVertices)
{
    answerVertices.clear();
    sort(vertices.begin(), vertices.end(), compare);
    DisjointSets disjointSets(nodeCount);

    for (auto [source, destination, weight] : vertices)
    {
        if (!disjointSets.areInSameSet(source, destination))
        {
            disjointSets.unite(source, destination);
            answerVertices.push_back(tuple<int, int, int>(source, destination, weight));
        }
        if (answerVertices.size() == nodeCount - 1)
            break;
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

    kruskal(nodeCount, vertices, answerVertices);

    int vertexWeights = 0;
    for (auto vertex : answerVertices)
        vertexWeights += get<2>(vertex);

    out << vertexWeights << '\n';
    out << answerVertices.size() << '\n';
    for (auto [source, destination, weight] : answerVertices)
        out << source << ' ' << destination << '\n';

    return 0;
}