#ifndef GRAPH_HPP
#define GRAPH_HPP

const int MAX = 1e3;

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// struct auxiliar para as arestas
struct Edge {
    int user;
    int job;
    int capacity;
    int flow;
};

class Graph {
    public:
        int numV;
        int indexV, indexE;
        unordered_map<string, int> input;
        unordered_map<string, int> inputE;
        vector<vector<int>> adjList;
        vector<vector<Edge>> graph;
        
        Graph(int U, int J);
        bool verify(string name);
        bool dfs(int u, int sink, vector<bool>& visited);
        int fordFulkerson();
        void addEdge(string &userName, string &jobName);
        void addEdgeExactly(string &userName, string &jobName);
        int greedyAlgorithm();
};

#endif // GRAPH_HPP