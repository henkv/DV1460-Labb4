#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
using namespace std;

class Node
{
private:
  int index;
  string name;

public:
  Node();
  Node(string name);
  virtual ~Node();

  int  getIndex();
  void setIndex(int index);

  string getName();
};

#endif
