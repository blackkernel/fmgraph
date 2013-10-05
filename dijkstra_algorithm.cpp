#include <iostream>
#include <priority_queue.h>
#include <dijkstra_algorithm.h>

using namespace fmgraph;
using namespace fmutil;

void DijkstraAlgorithm::solveShortestPath() {
  initializeSingleSource();
  while(true)
    {
      try {
        KeyValue frontierNode = pq.popElement();
        DirectedGraph::adjVector adjEdges = dg->getAdjacentEdges(frontierNode.key);
        for(auto it = adjEdges.begin(); it != adjEdges.end(); ++it) {
          //cout << "relaxing edge: " << (*it).toString() << endl;
          relax( (*it).from(),  (*it).to(), (*it).weight() );
        }
      }
      catch(KeyValuePriorityQueue::KeyError e) {
        break;
      }
    }
}

