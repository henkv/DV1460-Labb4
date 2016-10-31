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

		Node(T const& data, Node* prev = nullptr, Node* next = nullptr)
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
    
    void deleteNode(Node* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = nullptr;
        node->prev = nullptr;
        delete node;
    }
    
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
    
    void addFirst(T const& data)
    {
        if (this->root != nullptr)
        {
            this->root = new Node(data, this->root->prev, this->root);
            this->root->next->prev = this->root;
            this->root->prev->next = this->root;
        }
        else
        {
            this->root = new Node(data);
            this->root->next = this->root;
            this->root->prev = this->root;
        }
        this->nrOfNodes++;
    }

	void addLast(T const& data)
	{
        if (this->root != nullptr)
        {
            this->root->prev = new Node(data, this->root->prev, this->root);
            this->root->prev->prev->next = this->root->prev;
        }
        else
        {
            this->root = new Node(data);
            this->root->next = this->root;
            this->root->prev = this->root;
        }
        this->nrOfNodes++;
	}

	T removeFirst()
	{
		if (nrOfNodes == 0) throw new Exception("list empty");

		Node* oldRoot = this->root;
		T output = oldRoot->data;

		if (this->nrOfNodes == 1)
		{
			this->root = nullptr;
		}
		else
		{
			this->root = oldRoot->next;
		}

		this->deleteNode(oldRoot);
		this->nrOfNodes--;

		return data;
	}

	T removeLast()
	{
		if (nrOfNodes == 0) throw new Exception("list empty");

		Node* oldLast = this->root->prev;
		T output = oldLast->data;

		if (this->nrOfNodes == 1)
		{
			this->root = nullptr;
		}

		this->deleteNode(oldLast);
		this->nrOfNodes--;

		return data;
	}
    
    T removeAt(size_t index)
    {
		T output;

        if (index >= this->nrOfNodes)
        {
            throw new Exception("Index out of range");
        }
        
        
        if (index == 0)
        {
			output = this->removeFirst();
        }
		else if (index == this->nrOfNodes - 1)
		{
			output = this->removeLast();
		}
        else
        {
			Node* walker = this->root;
            for (size_t i = 0; i < index; i++) {
                walker = walker->next;
            }

			output = walker->data;

			if (this->nrOfNodes == 1)
			{
				this->root = nullptr;
			}

			this->deleteNode(walker);
			this->nrOfNodes--;			
        }   
        
		return output;
    }

	void push(T const& data)
	{
		this->addFirst(data);
	}

	void queue(T const& data)
	{
		this->addLast(data);
	}

	T pop()
	{
		return removeFirst();
	}
};

#endif // !DUALLINKLIST_H
