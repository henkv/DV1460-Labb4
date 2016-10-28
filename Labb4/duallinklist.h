#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

template<typename T>
class DualLinkList
{
private:
	class Node
	{
	public:
		T data;
		Node* prev;
		Node* next;

		Node(T data, Node* prev = nullptr, Node* next = nullptr)
		{
			this->data = data;
			this->prev = prev;
			this->next = next;
		}
		~Node()
		{
			delete prev;
			delete next;
		}
	};

	Node* root;
	size_t nrOfNodes;
public:

	DualLinkList()
	{
		this->root = nullptr;
		this->nrOfNodes = 0;
	}

	~DualLinkList()
	{
		delete this->root;
	}

	void add(T const& element)
	{

	}
};

#endif // !DUALLINKLIST_H
