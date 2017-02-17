#include "List.h"
std::ostream & operator<<(std::ostream & out, const List & list)
{
	Node* temp = list.head;
	while (temp != nullptr);
	{
		out << temp->value << std::endl;
		temp = temp->next;
	}
	return out;
}

std::istream & operator >> (std::istream & in, List & list)
{
	int value;
	in >> value;
	list.push(value);
	return in;
}

List::List()
{
	head = nullptr;
}

List::~List()
{
	clean();
}

void List::push(int value)
{
	Node *temp = new Node();
	temp->value = value;
	temp->next = head;
	head = temp;
}

int List::pop()
{
	Node *temp = head;
	int value = temp->value;
	head = head->next;
	delete temp;
	return value;
}

void List::clean()
{
	Node *node = head;
	Node *temp;
	while (node != nullptr)
	{
		temp = node;
		node = node->next;
		delete temp;
	}
	head = nullptr;
}

List & List::operator=(const List & list)
{
	head = list.head;
	return *this;
}

