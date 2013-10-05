#ifndef FMUTIL_PRIORITY_QUEUE_H
#define FMUTIL_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <sstream>

namespace fmutil {

  struct KeyValue { // Should be templetized to receive any key
  KeyValue(size_t k, double v, bool status = true) : key(k), value(v), valid(status) {};
    size_t key;
    double value;
    bool valid;
  
    std::string toString() const 
    { 
      std::ostringstream s;
      s << key << " -> " << value << (valid ? " valid" : " invalid");
      return s.str(); 
    }; 

    // Not neccessarily needed to declare it friend since all members are public
    friend bool operator>(const KeyValue& kv1, const KeyValue &kv2);
    friend bool operator<(const std::shared_ptr<KeyValue> kv1, const std::shared_ptr<KeyValue> kv2);
  };
  
  //Overload the > operator. Has to be global 
  inline bool operator>(const KeyValue& kv1, const KeyValue &kv2)
  {
   return kv1.value < kv2.value;	
  }

  //Overload the > operator. Has to be global 
  inline bool operator<(const std::shared_ptr<fmutil::KeyValue> kv1, const std::shared_ptr<fmutil::KeyValue> kv2)
  {
   return kv1->value < kv2->value;
  }

  class KeyValuePriorityQueue { // Class can handle updated priorities

  private:
    // Hide copy constructor, assignment operator

  public:
    bool empty() const { return pq.empty(); };
    void addElement(const KeyValue &kv);
    KeyValue popElement(); 
    void clear();
    class KeyError: public std::exception
     {
     public:
       virtual const char* what() const throw() {
         return "Pop from an empty queue"; 
       }
     };

  private:
    std::priority_queue<KeyValue, 
      std::vector<std::shared_ptr<KeyValue>>, 
      std::greater<std::vector<std::shared_ptr<KeyValue>>::value_type>> pq;

    
    std::map<size_t, std::shared_ptr<KeyValue>> validityMap;
  };

}

#endif //FMUTIL_PRIORITY_QUEUE_H
