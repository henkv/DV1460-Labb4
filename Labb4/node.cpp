#include "node.h"


Node::Node() {
  this->index = -1;
  this->name = "\0";
}

Node::Node(string name) {
  this->index = -1;
  this->name = name;
}

Node::~Node() {

}


int  Node::getIndex() {
  return this->index;
}

void Node::setIndex(int index) {
  this->index = index;
}

string Node::getName() {
  return this->name;
}
