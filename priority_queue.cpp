#include <priority_queue.h>
#include <iostream>

using namespace std;
using namespace fmutil;


// Add a new KeyValue or update the value of existing one
void KeyValuePriorityQueue::addElement(const KeyValue &kv) {

  shared_ptr<KeyValue> sp(new KeyValue(kv.key, kv.value, true)); 

  auto it = validityMap.find(kv.key);
  if ( it != validityMap.end() ) 
    {
      (it->second)->valid = false;
      validityMap.erase (it); 
    }
  validityMap.insert( std::pair<size_t, shared_ptr<KeyValue>>( kv.key, sp ));   
  pq.push(sp);
} 


// Pop a valid element, discard invalid elements 
KeyValue KeyValuePriorityQueue::popElement() {

  while( !pq.empty() )
    {
      shared_ptr<KeyValue> sp = pq.top();
      pq.pop();
      if ( sp->valid ) 
        {
           auto it = validityMap.find(sp->key);
           if ( it != validityMap.end() ) 
             validityMap.erase (it); 
           else
             cout << "Queue is not in good state, map does not contain key: " 
                  << sp->key << endl;
           return *sp;
        }
    }
  
  //popped last element which is invalid
  throw KeyError();
} 

void KeyValuePriorityQueue::clear() {
  pq = std::priority_queue<KeyValue, 
                           std::vector<std::shared_ptr<KeyValue>>, 
                           std::greater<std::vector<std::shared_ptr<KeyValue>>::value_type>>(); 
  validityMap.clear();
}
