#ifndef FMGRAPH_SHORTEST_PATH_ALGORITHM_H
#define FMGRAPH_SHORTEST_PATH_ALGORITHM_H

#include <map>
#include <memory>
#include <directed_graph.h>
#include <priority_queue.h>



namespace fmgraph {
  
  class ShortestPathAlgorithm {
  public:
  ShortestPathAlgorithm(size_t source_vertex, //check if valid source
                        const fmgraph::DirectedGraph* digraph) 
    : sourceV(source_vertex), dg(digraph) {};
    virtual void solveShortestPath() = 0;
    double getDistance(size_t v);
    size_t getPredecessor(size_t v);
    const std::map<size_t, double>& getDistances() const { return distance; };
    const std::map<size_t, double>& getPredecessors() const { return predecessor; };
    void reset();
    void setSource(size_t newSource); //check if it is valid
    void setGraph(const fmgraph::DirectedGraph* digraph);
  protected:
    void initializeSingleSource();
    void relax( size_t u, size_t v, double weight);
    size_t sourceV;
    const fmgraph::DirectedGraph *dg;
    fmutil::KeyValuePriorityQueue pq;
    std::map<size_t, double> distance;
    std::map<size_t, double> predecessor;
  };

};

#endif //FMGRAPH_SHORTEST_PATH_ALGORITHM_H
