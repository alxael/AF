#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>

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

int main()
{
    ifstream in("disjoint.in");
    ofstream out("disjoint.out");

    int nodeCount, operationsCount, type, source, destination;
    in >> nodeCount >> operationsCount;

    DisjointSets disjointSets(nodeCount);
    for (int operationIndex = 1; operationIndex <= operationsCount; operationIndex++)
    {
        in >> type >> source >> destination;
        if (type == 1)
            disjointSets.unite(source, destination);
        else if (type == 2)
            out << (disjointSets.areInSameSet(source, destination) ? "DA" : "NU") << '\n';
    }
    return 0;
}