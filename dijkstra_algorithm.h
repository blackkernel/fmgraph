#ifndef FMGRAPH_DIJKSTRA_ALGORITHM_H
#define FMGRAPH_DIJKSTRA_ALGORITHM_H

#include <map>
#include <memory>
#include <directed_graph.h>
#include <priority_queue.h>
#include <shortest_path_algorithm.h>


namespace fmgraph {
  
  class DijkstraAlgorithm : public ShortestPathAlgorithm {
  public:
  DijkstraAlgorithm(size_t source_vertex, //check if valid source
                    const fmgraph::DirectedGraph* digraph) 
    : ShortestPathAlgorithm(source_vertex, digraph) {};
    virtual void solveShortestPath();

  };

};
#endif //FMGRAPH_DIJKSTRA_ALGORITHM_H
