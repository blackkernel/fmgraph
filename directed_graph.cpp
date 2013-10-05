#include <iostream>
#include <sstream>
#include <vector>
#include <directed_graph.h>

using namespace fmgraph;
using namespace std;

// strip has a limitation where even if there is empty space between delimiters it pushes adds it to elems
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

GraphReader GraphReader::GraphReaderWithFile(const std::string &inputFile) {
  return GraphReader(inputFile);
};

int GraphReader::read() {

  
  inFileStream.open(this->inFileName); 
  if (inFileStream.is_open()) 
    {
      bool firstLine = true;
      string line;
      while (std::getline(this->inFileStream, line)) 
        {
          vector <string> fields;
          split(line, ' ', fields);
          
          if (firstLine) 
            {
              if (fields.size() != 2) {
                cout << "First line should be: [num_nodes] [num_edges]" << endl;
                return -1;
              }
              this->numV = (size_t)atoi(fields[0].c_str());
              this->numE = (size_t)atoi(fields[1].c_str());
              firstLine = false;
              cout << "NumNodes = " << this->numV << endl;
              cout << "NumEdges = " << this->numE << endl;
              continue;
            }
          
          if (fields.size() != 3) {
                cout << "Input file should contain [node_1] [node_2] [weight] " << endl;
                return -1;
          }

          DirectedEdge e(atoi(fields[0].c_str()),
                         atoi(fields[1].c_str()),
                         atoi(fields[2].c_str()));

          //cout << "NodeLeft: " << e.from()
          //     << " NodeRight: " << e.to()
          //     << " Cost: " << e.weight() << endl;

          this->edges.push_back(e);

        }
      inFileStream.close();
      cout << "Closing file, reader done reading" << endl;
    } 
  else 
    {
      cout << "Unable to open file:" << this->inFileName << endl; 
      return -1;
    }

  return 0;
} //GraphReader::read() 

DirectedGraph::DirectedGraph(const std::vector<DirectedEdge> &edges) {
  vector<DirectedEdge>::const_iterator cit = edges.begin();
  for(; cit != edges.end(); ++cit) {
    addEdge(*cit);
  }
}

void DirectedGraph::addEdges(const std::vector<DirectedEdge> &edges) { 
  vector<DirectedEdge>::const_iterator cit = edges.begin();
  for(; cit != edges.end(); ++cit) {
    addEdge(*cit);
  }
}

void DirectedGraph::addEdge(const DirectedEdge &edge) { 
  edges.push_back(edge);
  nodes.insert(edge.from());
  nodes.insert(edge.to());

  auto it = adjMap.find(edge.from());
  if ( it != adjMap.end() )
    (it->second).push_back(edge);
  else {
    adjMap.insert( std::pair<int, adjVector>( edge.from(), adjVector{edge} ));  //C++11 initialization list for vector
  }
}

const std::vector<DirectedEdge>& DirectedGraph::getAdjacentEdges(size_t v) const {
  auto it = adjMap.find(v);
  if ( it != adjMap.end() )
    return it->second; 
  else {
    NoAdjacentEdges exc;
    throw exc;
  }
}
