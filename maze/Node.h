#pragma once
#include <cstdio>
#include "Location2D.h"

class Node : public Location2D
{
	Node* link;
public : 
	Node(int r = 0, int c = 0)
		:Location2D(r, c), link(NULL) {}
	Node* getLink() { return link; }
	void setLink(Node* p) { link = p; }
	void display() {
		printf("(%d, %d)", row, col);
	}
};