#include <iostream>
#include <vector>
using namespace std;

template <class T>
class queue
{
  vector <T> vec;
  public:
  queue() {vec={};}
  int size() {return(vec.size());}
  void push(int n) {vec.push_back(n);return;}
  void pop() {vec.erase(vec.begin());return;}
  
  int back() {return(vec[vec.size()-1]);}
  int front() {return(vec[0];}
                      
  bool empty() {if (vec.size()==0) return(true); return(false);}  
};
