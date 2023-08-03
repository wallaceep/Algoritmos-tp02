#include <iostream>
#include <sstream>

#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

int main(int argc, char const *argv[]) {
    int numUsers, numJobs, numQual;
    string userName, jobName;
    string source = "source";
    string sink = "sink";

    cin >> numUsers >> numJobs >> numQual;

    Graph graph(numUsers, numJobs);

    // Lê a entrada e armazena os vértices e arestas
    for(int i = 0; i < numQual; i++){
        cin >> userName >> jobName;
        graph.addEdge(userName, jobName);
        if(!graph.verify(userName))
            graph.addEdgeExactly(source, userName);
        if(!graph.verify(jobName))    
            graph.addEdgeExactly(jobName, sink);
        graph.addEdgeExactly(userName, jobName);
    }

    // output 
    cout << "Guloso: " << graph.greedyAlgorithm() << endl; 
    cout << "Exato: " << graph.fordFulkerson() << endl; 

    return 0;
}