#ifndef FMGRAPH_BELLMAN_FORD_ALGORITHM_H
#define FMGRAPH_BELLMAN_FORD_ALGORITHM_H

#include <shortest_path_algorithm.h>

namespace fmgraph {
  
  class BellmanFordAlgorithm : public ShortestPathAlgorithm {
  public:
  BellmanFordAlgorithm(size_t source_vertex, //check if valid source
                       const fmgraph::DirectedGraph* digraph) 
    : ShortestPathAlgorithm(source_vertex, digraph) , hasNegativeCycle_(false) {};
    virtual void solveShortestPath();
    bool hasNegativeCycle() const { return hasNegativeCycle_; };
  private:
    bool hasNegativeCycle_;
  };

};

#endif //FMGRAPH_BELLMAN_FORD_ALGORITHM_H
