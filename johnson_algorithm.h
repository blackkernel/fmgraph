#ifndef FMGRAPH_JOHNSON_ALGORITHM_H
#define FMGRAPH_JOHNSON_ALGORITHM_H

#include <dijkstra_algorithm.h>
#include <bellman_ford_algorithm.h>

namespace fmgraph {

  class JohnsonAlgorithm {
  public:
  JohnsonAlgorithm(const fmgraph::DirectedGraph* digraph) 
    : dg(digraph), hasNegativeCycle_(false)  {};
    void solveAllShortestPaths();
    bool hasNegativeCycle() const { return hasNegativeCycle_; };
  private:
    const fmgraph::DirectedGraph *dg;
    fmgraph::DirectedGraph edg;  // Contains auxiliary vertex s = 0
    fmgraph::DirectedGraph rwdg;  // Contains auxiliary vertex s = 0
    bool hasNegativeCycle_;
  };

};
#endif //FMGRAPH_JOHNSON_ALGORITHM_H
