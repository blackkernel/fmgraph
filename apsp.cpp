#include <iostream>
#include <chrono>
#include <directed_graph.h>
#include <priority_queue.h>
#include <dijkstra_algorithm.h>
#include <bellman_ford_algorithm.h>
#include <johnson_algorithm.h>

using namespace std;
using namespace fmgraph;
using namespace fmutil;

int main(int argc, char*argv[])
{
  if (argc>1)
    cout << "Input file: " << argv[1] << endl;
  else {
    cout << "Please specify input file with graph input" << endl;
    return -1;
  }

  // Read Graph
  GraphReader reader = GraphReader::GraphReaderWithFile(argv[1]);
  reader.read();
  DirectedGraph digraph(reader.getEdges());
  cout << "Number of vertices added: " << digraph.V() << endl;
  cout << "Number of edges added: " << digraph.E() << endl;
 
  // Start timer
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);

  // Run Johnson Algorithm
  cout << "Running Johnson all-shortest-paths algorithm on graph." << endl;
  cout << "Starting time: " << std::ctime(&start_time);
  JohnsonAlgorithm johnson(&digraph);
  johnson.solveAllShortestPaths();

  // End timer
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
  std::cout << "Finished computation at " << std::ctime(&end_time)
            << "Elapsed time: " << elapsed_seconds.count() << "s\n";


}

