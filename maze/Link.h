#pragma once
#include "Node.h"

class LinkedQueue {
	Node* front;
	Node* rear;

public:

	LinkedQueue() :front(NULL) {}
	~LinkedQueue() { while (!isEmpty())delete dequeue(); }

	bool isEmpty() { return front == NULL; }

	void enqueue(Node* p) {
		if (isEmpty())front = rear = p;
		else {
			rear->setLink(p);
			rear = p;
		}
	}

	Node* dequeue() {
		if (isEmpty())return NULL;
		Node* p = front;
		front = front->getLink();
		if (front == NULL)rear = NULL;
		return p;
	}

	Node* peek() { return front; }

	void display() {
		printf("[링크스택]:");
		for (Node* p = front; p != NULL; p = p->getLink())
			p->display();
		printf("\n");
	}

};
