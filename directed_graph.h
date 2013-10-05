#ifndef FMGRAPH_DIRECTED_GRAPH_H
#define FMGRAPH_DIRECTED_GRAPH_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <exception>

namespace fmgraph {

  class DirectedEdge {

  public:
  DirectedEdge(size_t u, size_t v, double weight) : src(u), dest(v), w(weight) {};
    double weight() const { return this->w; };
    size_t from() const { return this->src; } ;
    size_t to() const { return this->dest; } ;
    std::string toString() const 
      { 
        std::ostringstream s;
        s << this->src << " --> " << this->dest << "   weight = " << this->w;
        return s.str(); 
      }; 

  private:
    size_t src;
    size_t dest;
    double w;

  };

  class GraphReader { 

  public:
    static GraphReader GraphReaderWithFile(const std::string &inputFile);
    int read();
    const std::vector<DirectedEdge>& getEdges() const { return edges; };
    size_t numVertices() const { return numV; }
    size_t numEdges() const { return numE; }

  private:
  GraphReader(std::string inputFile) : inFileName(inputFile) {};
    std::ifstream inFileStream; 
    std::string inFileName;
    size_t numV;
    size_t numE;
    std::vector<DirectedEdge> edges;
  
  };


   class DirectedGraph {
   
   public:
     DirectedGraph(const std::vector<DirectedEdge> &edges);
     DirectedGraph() {} ;
     void addEdge(const DirectedEdge &edge);
     void addEdges(const std::vector<DirectedEdge> &edges);
     const std::set<size_t> & getNodes() const { return nodes; };
     const std::vector<DirectedEdge>& getEdges() const { return edges; };
     const std::vector<DirectedEdge>& getAdjacentEdges(size_t v) const;
     size_t V() const { return nodes.size(); };
     size_t E() const { return edges.size(); };
     
     typedef std::vector<DirectedEdge> adjVector;

     class NoAdjacentEdges: public std::exception
     {
       virtual const char* what() const throw() {
       return "Node has no edges"; 
       }
     };
     

   private:
     const DirectedGraph& operator=( const DirectedGraph& );
     std::set<size_t> nodes;
     std::vector<DirectedEdge> edges;
     std::map<int, adjVector> adjMap;
        
  };

};

#endif //FMGRAPH_DIRECTED_GRAPH_H
