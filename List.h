#pragma once
//Fahad Waheed

template <typename T>
class List
{
	struct Node
	{
		T data;
		Node* next, * previous;

		Node() : data(T()), next(NULL), previous(NULL) {};

		Node(T data) : data(data), next(NULL), previous(NULL) {};
	};

	Node* head, * tail;

	void firstNodeCreation(T data)
	{
		Node* newNode = new Node(data);
		head = tail = newNode;
	}

	Node* Search(T data)
	{
		Node* currnode = head;
		while (currnode && currnode->data != data)
			currnode = currnode->next;
		return currnode;
	}

public:
	List() : head(NULL), tail(NULL) {};

	List(const List<T>& obj) : head(NULL), tail(NULL)
	{
		Node* currnode = obj.head;
		while (currnode)
		{
			this->Insert(currnode->data);
			currnode = currnode->next;
		}
	}

	List& operator=(const List<T>& obj)
	{
		this->clear();
		Node* currnode = obj.head;
		while (currnode)
		{
			this->Insert(currnode->data);
			currnode = currnode->next;
		}
		return *this;
	}

	bool isEmpty()
	{
		return head == NULL && tail == NULL;
	}

	void Insert(T data)
	{
		if (isEmpty())
			firstNodeCreation(data);
		else if (data < head->data)
		{
			Node* newNode = new Node(data);
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
		else
		{
			Node* currnode = head->next;
			Node* newNode = new Node(data);

			while (currnode && data > currnode->data)
				currnode = currnode->next;

			if (currnode == NULL)
			{
				newNode->previous = tail;
				tail->next = newNode;
				tail = newNode;
			}
			else
			{
				newNode->next = currnode;
				newNode->previous = currnode->previous;
				currnode->previous->next = newNode;
				currnode->previous = newNode;
			}
		}
	}

	void Remove(T data)
	{
		Node* dNode = Search(data);
		if (dNode)
		{
			if (dNode == head && dNode == tail)
			{
				head = tail = NULL;
			}
			else if (dNode == head)
			{
				head->next->previous = NULL;
				head = head->next;
			}
			else if (dNode == tail)
			{
				tail->previous->next = NULL;
				tail = tail->previous;
			}
			else
			{
				dNode->previous->next = dNode->next;
				dNode->next->previous = dNode->previous;
			}

			delete dNode;
		}
	}

	void Update(T oldData, T newData)
	{
		Node* currnode = Search(oldData);

		if (currnode)
			currnode->data = newData;
	}

	int Find(T data)
	{
		int count = 0;

		Node* currnode = head;
		while (currnode && currnode->data != data)
		{
			currnode = currnode->next;
			count++;
		}

		if (currnode) 
			return count;
		return -1;
	}

	class Interator
	{
		Node* it;

	public:
		Interator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = node;
		}

		T operator*()
		{
			return it->data;
		}

		void operator++()
		{
			it = it->next;
		}

		void operator++(int)
		{
			it = it->next;
		}

		bool operator==(Node* node)
		{
			return this->it == node;
		}

		bool operator!=(Node* node)
		{
			return this->it != node;
		}
	};

	Node* begin()
	{
		return head;
	}

	Node* end()
	{
		if (tail)
			return tail->next;
		return NULL;
	}

	void clear()
	{
		Node* currnode = head;
		while (currnode)
		{
			head = head->next;
			delete currnode;
			currnode = head;
		}
		tail = head;
	}

	T operator[](int index)
	{
		int i = 0;
		Node* currnode = head;
		while (currnode && i != index)
		{
			currnode = currnode->next;
			i++;
		}
		if (currnode)
			return currnode->data;
		return T();
	}

	~List()
	{
		clear();
	}
};
