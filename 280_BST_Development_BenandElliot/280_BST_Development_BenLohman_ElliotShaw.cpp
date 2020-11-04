/*
280
BST_Development
Ben Lohman, Elliot Shaw
*/

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Node {
	int data;
	Node* left, * right;
};

class BST {
private:
	Node* root;
	Node* insert(int, Node*); //helper
	int getSize(Node*); //helper
	void displayInOrder(Node*); //helper
	Node* find(int, Node*);//helper
	int getHeight(Node*, int);//helper
	void displayPreOrder(Node*);//helper
	bool isLeaf(Node*);
	int countLeaves(Node*);//helper
public:
	void displayPreOrder();
	int getHeight();
	BST();
	void insert(int);
	void displayInOrder();
	int getSize();
	void load(int, int, int);
	void insertNonRecursive(int);
	Node* find(int);
	int count(int);
	void del(int);
	int countLeaves();
	int maxValue();
}; //BST class

//helper functions

Node* BST::insert(int v, Node* r) {
	if (r == nullptr) {
		r = new Node;
		r->left = r->right = nullptr;
		r->data = v;
		return r;
	}
	else if (v < r->data) {
		r->left = insert(v, r->left);
		return r;
	}
	else {
		r->right = insert(v, r->right);
		return r;
	}
} //insert helper

Node* BST::find(int v, Node* r) {
	while (r != nullptr) {
		if (r->data == v) {
			return r;
		}
		else if (v < r->data) {
			r = r->left;
		}
		else {
			r = r->right;
		}
	}
	return nullptr;
}//find helper

void BST::displayPreOrder(Node* r) {
	if (r != nullptr)
	{
		cout << r->data << endl;
		displayPreOrder(r->left);
		displayPreOrder(r->right);
	}
}//displayPreOrder helper

void BST::displayInOrder(Node* r) {
	if (r != nullptr)
	{
		displayInOrder(r->left);
		cout << r->data << endl;
		displayInOrder(r->right);
	}
} //displayInOrder helper

int BST::getHeight(Node* r, int c) {
	if (r != nullptr)
	{
		c++;
		int left = getHeight(r->left, c);
		int right = getHeight(r->right, c);
		if (left > right) {
			c = left;
		}
		else {
			c = right;
		}
	}
	return c;
}//getHeight helper

bool BST::isLeaf(Node* r) {
	if (r->right == nullptr && r->left == nullptr) {
		return true;
	}
	return false;
}//isLeaf helper

int BST::countLeaves(Node* r) {
	int c = 0;
	if (isLeaf(r)) {
		return 1;
	}
	if (r->left != nullptr) {
		c += countLeaves(r->left);
	}
	if (r->right != nullptr) {
		c += countLeaves(r->right);
	}
	return c;
}//countLeaves helper

int BST::getSize(Node* r) {
	if (r == nullptr)
		return 0;
	else
		return 1 + getSize(r->left) + getSize(r->right);
} //getSize helper

//constructors

BST::BST() {
	root = nullptr;
} //BST


//setters

void BST::insert(int v) {
	root = insert(v, root);
} //insert

void BST::load(int c, int min, int max) {
	srand(time(NULL));
	for (int i = 0; i < c; i++){
		root = insert((rand()%(max-min)) +min, root);
	}
}//load

void BST::insertNonRecursive(int v) {
	Node* check = root;
	Node* checkptr = nullptr;
	while (check != nullptr) {
		checkptr = check;
		if (v < checkptr->data) {
			check = check->left;
		}
		else {
			check = check->right;
		}
	}
	if(checkptr == nullptr){
		root = new Node;
		root->left = root->right = nullptr;
		root->data = v;
	}
	else if (v < checkptr->data) {
		checkptr->left = new Node;
		checkptr->left->data = v;
		checkptr->left->left = nullptr;
		checkptr->left->right = nullptr;
	}
	else {
		checkptr->right = new Node;
		checkptr->right->data = v;
		checkptr->right->left = nullptr;
		checkptr->right->right = nullptr;
	}
}//insertNonRecursive 


//getters

int BST::getHeight() {
	return getHeight(root, 0);
} //getHeight;

int BST::getSize() {
	return getSize(root);
} //getSize

int BST::maxValue() {
	//pre-req: the tree is not an empty tree
	Node* r = root;
	while (r->right != nullptr) {
		r = r->right;
	}
	return r->data;
}//maxValue

//utility

Node* BST::find(int v) {
	return find(v, root);
}//find

int BST::count(int v) {
	Node* r = root;
	int count = 0;
	while (r != nullptr) {
		if (r->data == v) {
			count++;
		}
		if (v < r->data) {
			r = r->left;
		}
		else {
			r = r->right;
		}
	}
	return count;
}//count

void BST::displayInOrder() {
	displayInOrder(root);
} //displayInOrder

void BST::displayPreOrder() {
	displayPreOrder(root);
}//displayPreOrder

int BST::countLeaves() {
	return countLeaves(root);
}//countLeaves

void BST::del(int v) {
	Node* t = find(v, root);
	int tval = t->data;
	Node* p= root;
	if (t != root) {
		while (p->left != t && p->right != t) {
			if (tval < p->data) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}
		if (p->left == t) {
			p->left = nullptr;
		}
		else {
			p->right = nullptr;
		}
	}
	else {
		root = nullptr;
	}
	Node* ip = nullptr;
	while(!isLeaf(t)){
		Node* i = t;
		
		while (!isLeaf(i)) {
			ip = i;
			if (i->right != nullptr) {
				i = i->right;
			}
			else {
				i = i->left;
			}
		}
		insert(i->data);
		if (ip->right != nullptr) {
			ip->right = nullptr;
		}
		else {
			ip->left = nullptr;
		}
		free(i);
	}
	free(t);
}//delete

int main() {
	BST bst1 = BST();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(20);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(10);
	bst1.insert(30);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(5);
	bst1.insert(40);
	bst1.insert(25);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(0);
	bst1.insert(2);
	bst1.insert(-5);
	bst1.insert(-2);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	BST bst2 = BST();
	bst2.load(10, -20, 20);
	bst2.displayInOrder();
	cout << "Size: " << bst2.getSize() << endl << endl;
	bst2.insertNonRecursive(20);
	bst2.displayInOrder();
	cout << "Size: " << bst2.getSize() << endl << endl;
	cout << "address of 20: " << bst2.find(20)<< endl << endl;
	bst2.insert(45);
	bst2.insert(45);
	bst2.insert(45);
	bst2.insert(45);
	bst2.insert(45);
	cout << "count of 45s: " << bst2.count(45)<< endl << endl;
	bst2.displayInOrder();
	cout << endl;
	bst2.del(20);
	bst2.displayInOrder();
	cout << endl;
	cout << "height of bst2: " << bst2.getHeight()<<endl <<endl;
	bst2.displayPreOrder();
	cout << endl << "number of leaves: " << bst2.countLeaves() << endl << endl;
	cout << "Max value: " << bst2.maxValue();
} //main
