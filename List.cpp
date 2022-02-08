#include "List.h"

void List::enqueue(double value)
{
	if (this->head == nullptr || this->tail == nullptr)
	{
		this->head = new Node(value);
		this->tail = this->head;
	}
	else
	{
		this->tail->next = new Node(value);
		this->tail->next->prev = this->tail;
		this->tail = this->tail->next;
	}
}

double List::dequeueFirst()
{
	double res = this->head->value;

	Node* tmp = this->head;
	this->head = this->head->next;
	delete tmp;

	return res;
}

double List::dequeueLast()
{
	double res = this->tail->value;

	Node* tmp = this->tail;
	this->tail = this->tail->prev;
	delete tmp;

	return res;
}

void List::print() const
{
	Node* tmp = this->head;
	while (tmp != nullptr)
	{
		std::cout << tmp->value << "\t";
		tmp = tmp->next;
	}
}

List::~List()
{
	while (this->head != nullptr)
	{
		Node* tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}
}
