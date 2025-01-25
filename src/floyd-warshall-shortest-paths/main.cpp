#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

void floydWarshall(vector<vector<int>> &distances, vector<vector<int>> &shortestPaths)
{
    shortestPaths = distances;

    for (int intermediaryIndex = 0; intermediaryIndex < shortestPaths.size(); intermediaryIndex++)
        for (int sourceIndex = 0; sourceIndex < shortestPaths.size(); sourceIndex++)
            for (int destinationIndex = 0; destinationIndex < shortestPaths.size(); destinationIndex++)
                if (sourceIndex != destinationIndex)
                    if (shortestPaths[sourceIndex][intermediaryIndex] && shortestPaths[intermediaryIndex][destinationIndex] &&
                        (shortestPaths[sourceIndex][destinationIndex] > shortestPaths[sourceIndex][intermediaryIndex] + shortestPaths[intermediaryIndex][destinationIndex] || !shortestPaths[sourceIndex][destinationIndex]))
                        shortestPaths[sourceIndex][destinationIndex] = shortestPaths[sourceIndex][intermediaryIndex] + shortestPaths[intermediaryIndex][destinationIndex];
}

int main()
{
    ifstream in("royfloyd.in");
    ofstream out("royfloyd.out");

    int nodeCount, distance;
    in >> nodeCount;

    vector<vector<int>> distances(nodeCount, vector<int>(nodeCount, 0)), shortestPaths;
    for (int sourceIndex = 0; sourceIndex < distances.size(); sourceIndex++)
        for (int destinationIndex = 0; destinationIndex < distances.size(); destinationIndex++)
            in >> distances[sourceIndex][destinationIndex];

    floydWarshall(distances, shortestPaths);

    for (int sourceIndex = 0; sourceIndex < shortestPaths.size(); sourceIndex++)
    {
        for (int destinationIndex = 0; destinationIndex < shortestPaths.size(); destinationIndex++)
            out << shortestPaths[sourceIndex][destinationIndex] << ' ';
        out << '\n';
    }

    return 0;
}