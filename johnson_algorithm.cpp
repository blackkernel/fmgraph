#include <iostream>
#include <johnson_algorithm.h>

using namespace std;
using namespace fmgraph;
using namespace fmutil;

void JohnsonAlgorithm::solveAllShortestPaths() {

  // Create new graph with extra source s = 0 connected to all vertices
  // with 0 weights
  
  edg.addEdges( dg->getEdges() );
  
  size_t auxiliaryVertex = 0;
  set<size_t> nodes = dg->getNodes();
  for ( auto nit = nodes.begin(); nit != nodes.end(); ++nit)
    {
      edg.addEdge(DirectedEdge(auxiliaryVertex, *nit, 0));
    }

  // Run Bellman-Ford on the extended graph
  BellmanFordAlgorithm bellmanFord(auxiliaryVertex, &edg);
  cout << "Runing Bellman-Ford with source vertex: " << auxiliaryVertex << endl;
  bellmanFord.solveShortestPath();
  
  hasNegativeCycle_ = bellmanFord.hasNegativeCycle();
  cout << "Graph " 
       << (hasNegativeCycle_ ? "has" : " does not have")
       << " negative cycles." 
       << endl;
  
  if ( hasNegativeCycle_ )
      return;

  // Construct reweighted digraph using shortest paths from Bellman-Ford
  vector<DirectedEdge> edges = edg.getEdges();
  for(auto it = edges.begin(); it != edges.end(); ++it) 
    {
      if ( (*it).from() == auxiliaryVertex ) 
        continue;
      
      double newWeight = (*it).weight() + bellmanFord.getDistance((*it).from())
                                        - bellmanFord.getDistance((*it).to());
      rwdg.addEdge(DirectedEdge( (*it).from(), (*it).to(), newWeight ));
    }
  
  // Run Dijkstra for every edge in reweighted graph
  cout << "Running Dijkstra for all vertexes" << endl;
  double shortestShortestPath = numeric_limits<double>::max();
  int numIterations = 0;
  for ( auto nitu = nodes.begin(); nitu != nodes.end(); ++nitu)
    {
      if ( ++numIterations % 10000 == 0 )
        cout << "Running Dijkstra for source node: " << *nitu << endl;

      DijkstraAlgorithm dijkstra(*nitu, &rwdg);
      // TODO: Put all distances in a 2d array, d(u,v) = d_dijkstra(u,v) + h[v] - h[u]
      //       Also, put distances in a min priority_queue for easy access to shortest-shortest
      for(auto nitv = nodes.begin(); nitv != nodes.end(); ++nitv)
        {
          double dist = dijkstra.getDistance(*nitv) + bellmanFord.getDistance((*nitv))
                                                   - bellmanFord.getDistance((*nitu));
        
          if ( dist < shortestShortestPath )
            shortestShortestPath = dist;
        }
    }

  cout << "Johnson shortest shortest path for graph is: " << shortestShortestPath << endl;
    
  }


  





