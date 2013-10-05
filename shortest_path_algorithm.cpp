#include <iostream>
#include <priority_queue.h>
#include <shortest_path_algorithm.h>

using namespace std;
using namespace fmgraph;
using namespace fmutil;


double ShortestPathAlgorithm::getDistance(size_t v) {
  return distance[v];
}

size_t ShortestPathAlgorithm::getPredecessor(size_t v) {
  return predecessor[v];
}


void ShortestPathAlgorithm::initializeSingleSource() {
  set<size_t> nodes = dg->getNodes();
  for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
      distance[*it] = std::numeric_limits<size_t>::max();
      predecessor[*it] = -1;
    }
  distance[sourceV] = 0;
  predecessor[sourceV] = 0;
  pq.addElement(KeyValue(sourceV,0));
}

void ShortestPathAlgorithm::relax( size_t u, size_t v, double weight) {
  if ( distance[v] > distance[u] + weight )
    {   
      distance[v] = distance[u] + weight; 
      predecessor[v] = u;
      KeyValue kv(v, distance[v]);
      pq.addElement(kv);
    }
}

void ShortestPathAlgorithm::reset() {
  distance.clear();
  predecessor.clear();
  pq.clear();
}

void ShortestPathAlgorithm::setSource(size_t newSource) {
  sourceV = newSource;
}

void ShortestPathAlgorithm::setGraph(const fmgraph::DirectedGraph* digraph) {
  dg = digraph;
}

