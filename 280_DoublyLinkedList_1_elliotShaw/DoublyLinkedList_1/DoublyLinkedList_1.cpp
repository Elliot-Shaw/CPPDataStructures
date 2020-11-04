/* 
Elliot Shaw
DoublyLinkedList_1
280
*/
#include <iostream>
#include <string>
using namespace std;

struct Node {
	int data;
	Node* next, * prev;
};

class DoublyLinkedList {
private:
	Node* top, * bottom;
	int size;
public:
	//constructors
	DoublyLinkedList();
	//setters
	void addNodeTop(int);
	void addNodeBottom(int);
	void deleteTop();
	void deleteBottom();
	void deleteAt(Node* p);
	void insertBefore(Node* p, int v);
	void insertAfter(Node* p, int v);
	void set(Node* p, int v);
	//getters
	int get(Node* p);
	int getSize();
	int getTop();
	Node* getTopP();
	int getBottom();
	int howMany(int v);
	Node* findFirst(int v);
	Node* findLast(int v);
	//utility
	void displayFromTop();
	void displayFromBottom();
};  //DoublyLinkedList

DoublyLinkedList::DoublyLinkedList() {
	top = bottom = nullptr;
	size = 0;
} //DoublyLinkedList

void DoublyLinkedList::addNodeTop(int v) {
	Node* p = new Node;
	p->data = v;
	p->next = top;
	p->prev = nullptr;
	if (size == 0)
		bottom = p;
	else
		top->prev = p;
	top = p;
	size++;
} //addNodeTop		O(1)

void DoublyLinkedList::addNodeBottom(int v) {
	Node* p = new Node;
	p->data = v;
	p->prev = bottom;
	p->next = nullptr;
	if (size == 0)
		top = p;
	else
		bottom->next = p;
	bottom = p;
	size++;
} //addNodeBottom		O(1)

void DoublyLinkedList::deleteTop() {
	if (top != nullptr) {
		Node* temp = top;
		if (top == bottom)
			top = bottom = nullptr;
		else {
			top = top->next;
			top->prev = nullptr;
		}
		delete temp;
		size--;
	}
} //deleteTop		O(1)

void DoublyLinkedList::deleteBottom() {
	if (bottom != nullptr) {
		Node* temp = bottom;
		if (bottom == top)
			bottom = top = nullptr;
		else {
			bottom = bottom->prev;
			bottom->next = nullptr;
		}
		delete temp;
		size--;
	}
} //deleteBottom		O(1)

void DoublyLinkedList::deleteAt(Node* p) {
	if (p == top) {
		deleteTop();
		size--;
	}
	else if (p == bottom) {
		deleteBottom();
		size--;
	}
	else {
		p->next->prev = p->prev;
		p->prev->next = p->next;
		delete p;
		size--;
	}
} //deleteAt		O(1)

void DoublyLinkedList::insertBefore(Node* p, int v) {
	Node* temp = new Node;
	temp->data = v;
	if (p == top) {
		temp->prev = nullptr;
		temp->next = p;
		top->prev = temp;
		top = temp;
	}
	else {
		temp->prev = p->prev;
		temp->next = p;
		p->prev = temp;
		temp->prev->next = temp;
	}
	size++;
} //insertBefore		O(1)

void DoublyLinkedList::insertAfter(Node* p, int v) {
	if (p == bottom) {
		Node* temp = new Node;
		temp->data = v;

		temp->next = nullptr;
		temp->prev = p;
		bottom->next = temp;
		bottom = temp;
		size++;
	}
	else {
		insertBefore(p->next, v);
	}
	
} //insertAfter		O(1)

Node* DoublyLinkedList::findFirst(int v) {
	Node* runner = top;
	
	while (runner != nullptr) {
		if (runner->data == v)
			return runner;
		runner = runner->next;
	}
	return nullptr;
} //findFirst		O(n)

Node* DoublyLinkedList::findLast(int v) {
	Node* runner = bottom;
	
	while (runner != nullptr) {
		if (runner->data == v)
			return runner;
		runner = runner->prev;
	}
	return nullptr;
} //findLast		O(n)

int DoublyLinkedList::howMany(int v) {
	Node* runner = top;
	int count = 0;
	while (runner != nullptr) {
		if (runner->data == v)
			count++;
		runner = runner->next;
	}
	return count;
} //howMany		O(n)

void DoublyLinkedList::set(Node* p, int v) {
	p->data = v;
} //set		O(1)

int DoublyLinkedList::get(Node* p) {
	return p->data;
} //get		O(1)

int DoublyLinkedList::getTop() {
	return top->data;
} //getTop		O(1)

int DoublyLinkedList::getBottom() {
	return bottom->data;
} //getBottom		O(1)

void DoublyLinkedList::displayFromTop() {
	Node* runner = top;
	while (runner != nullptr) {
		cout << runner->data << endl;
		runner = runner->next;
	}
} //displayFromTop		O(n)

void DoublyLinkedList::displayFromBottom() {
	Node* runner = bottom;
	while (runner != nullptr) {
		cout << runner->data << endl;
		runner = runner->prev;
	}
} //displayFromBottom		O(n)

int DoublyLinkedList::getSize() {
	return size;
}; //getSize		O(1)

Node* DoublyLinkedList::getTopP() {
	return top;
} //getTopP		O(1)


int main() {

	DoublyLinkedList dl1 = DoublyLinkedList();


	dl1.addNodeTop(12);

	dl1.addNodeTop(50);

	dl1.addNodeTop(-88);

	dl1.addNodeBottom(-1);

	dl1.addNodeBottom(-2);

	dl1.addNodeBottom(-3);

	cout << "Display from top 1..." << endl;

	dl1.displayFromTop();

	cout << "Display from bottom 1..." << endl;

	dl1.displayFromBottom();

	cout << endl;



	dl1.deleteBottom();

	cout << "Display from top 2..." << endl;

	dl1.displayFromTop();

	cout << "Display from bottom 2..." << endl;

	dl1.displayFromBottom();

	cout << "Size: " << dl1.getSize() << endl << endl;



	Node* temp = dl1.getTopP(); //write this temporary function for testing, all it does is return the top pointer

							   //it’s used so that we can have a pointer to deleteAt

	Node* r = temp->next; //change this line ---------------------------------------------------

	dl1.deleteAt(r);

	cout << "Display from top 3..." << endl;

	dl1.displayFromTop();

	cout << "Display from bottom 3..." << endl;

	dl1.displayFromBottom();

	cout << "Size: " << dl1.getSize() << endl << endl;



	r = dl1.findFirst(12);

	cout << "Value found: " << r->data << endl << endl;



	dl1.insertAfter(r, 999);

	cout << "Display from top 4..." << endl;

	dl1.displayFromTop();

	cout << "Display from bottom 4..." << endl;

	dl1.displayFromBottom();

	cout << "Size: " << dl1.getSize() << endl << endl;

} //main
