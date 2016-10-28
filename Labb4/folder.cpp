#include "folder.h"

Folder::Folder() : Node() {
}

Folder::Folder(string name) : Node(name) {
}

Folder::~Folder() {
	for (Node* node : this->children) {
		delete node;
	}
}

Node * Folder::getChild(string name)
{
	Node* output = nullptr;

	for (Node* child : this->children) {
		if (name == child->getName()) {
			output = child;
			break;
		}
	}

	return output;
}

bool Folder::addChild(Node * node) {
	bool output = false;

	if (this->getChild(node->getName()) == nullptr) {
		this->children.push_back(node);
		output = true;
	}

	return output;
}

vector<Node*> Folder::getChildren() {
	return this->children;
}
