#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

void dfs(int node,
         vector<vector<int>> &adjancencyMatrix,
         vector<vector<int>> &answer,
         vector<bool> &visited,
         vector<bool> &processed,
         vector<int> &number,
         vector<int> &lowest,
         stack<int> answerStack,
         int &counter)
{
    visited[node] = true;
    number[node] = ++counter;
    lowest[node] = number[node];
    answerStack.push(node);

    for (auto it = adjancencyMatrix[node].begin(); it != adjancencyMatrix[node].end(); it++)
    {
        if (!visited[*it])
        {
            cout << node << " -> " << *it << '\n';
            dfs(*it, adjancencyMatrix, answer, visited, processed, number, lowest, answerStack, counter);
            lowest[node] = min(lowest[node], lowest[*it]);
        }
        else if (!processed[*it])
            lowest[node] = min(lowest[node], number[*it]);
    }

    processed[node] = true;

    if (number[node] == lowest[node])
    {
        vector<int> connectedComponent;
        while (!answerStack.empty() && answerStack.top() != node)
        {
            connectedComponent.push_back(answerStack.top());
            cout << "popped " << answerStack.top() << '\n';
            answerStack.pop();
        }
        if (!answerStack.empty())
        {
            cout << "popped " << answerStack.top() << '\n';
            answerStack.pop();
        }
        connectedComponent.push_back(node);

        answer.push_back(connectedComponent);
    }
}

int main()
{
    ifstream in("ctc.in");
    ofstream out("ctc.out");

    int nodeCount, vertexCount, source, destination;
    in >> nodeCount >> vertexCount;

    vector<vector<int>> adjancencyMatrix(nodeCount + 1, vector<int>()), answer;
    vector<bool> visited(nodeCount + 1, false), processed(nodeCount + 1, false);
    vector<int> number(nodeCount + 1, -1), lowest(nodeCount + 1, -1);
    stack<int> answerStack;

    for (int vertexIndex = 1; vertexIndex <= vertexCount; vertexIndex++)
    {
        in >> source >> destination;
        adjancencyMatrix[source].push_back(destination);
    }

    int counter = 0;
    for (int nodeIndex = 1; nodeIndex <= nodeCount; nodeIndex++)
        if (!visited[nodeIndex])
            dfs(nodeIndex, adjancencyMatrix, answer, visited, processed, number, lowest, answerStack, counter);

    out << answer.size() << '\n';
    for (auto itComponent = answer.begin(); itComponent != answer.end(); itComponent++)
    {
        for (auto it = itComponent->begin(); it != itComponent->end(); it++)
            out << *it << ' ';
        out << '\n';
    }

    return 0;
}