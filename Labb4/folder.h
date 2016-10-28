#ifndef FOLDER_H
#define FOLDER_H
#include <vector>
#include "node.h"
using namespace std;

class Folder : public Node
{
private:
	vector<Node*> children;

public:
	Folder();
	Folder(string name);
	virtual ~Folder();

	Node* getChild(string name);
	bool  addChild(Node* node);

	vector<Node*> getChildren();
};

#endif
