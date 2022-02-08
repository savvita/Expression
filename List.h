#pragma once
#include<iostream>

struct Node
{
	double value;
	Node* next;
	Node* prev;

	Node(double value)
	{
		this->value = value;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

class List
{
private:
	Node* head;
	Node* tail;

public:
	List() :head{ NULL }, tail{ NULL }
	{

	}

	void enqueue(double value);

	double dequeueFirst();

	double dequeueLast();

	void print() const;

	~List();
};

