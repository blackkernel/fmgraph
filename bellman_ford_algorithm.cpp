#include <iostream>
#include <bellman_ford_algorithm.h>

using namespace fmgraph;
using namespace fmutil;
using namespace std;

void BellmanFordAlgorithm::solveShortestPath() {
  initializeSingleSource();

  cout << "Starting Bellman-Ford for number of nodes in graph: " << dg->V() << endl;

  std::vector<DirectedEdge> edges = dg->getEdges(); 

  for(size_t i = 0; i < dg->V(); ++i)
    {
      if ( i % 10 == 0  )
        cout << "BM at repetition: " << i << " out of " << dg->V() << endl;

      for(auto it = edges.begin(); it != edges.end(); ++it) 
        {
          relax( (*it).from(),  (*it).to(), (*it).weight() );
        }
    }

  // Detect negative cycles
  for(auto it = edges.begin(); it != edges.end(); ++it) 
    {
      if ( distance[(*it).to()] > distance[(*it).from()] + (*it).weight() ) {
        hasNegativeCycle_ = true;
        // Invalidate all paths and distances
      }
    }
  
}
