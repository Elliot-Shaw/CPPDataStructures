/*
280
Graph Assignment 1
Elliot Shaw, Ben Lohman
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Node {
	char lable;
	vector<Node*> links;
	vector<int> weights;
};

void adjacent(const vector<Node*>& links, const char lable) {
	int i;
	for (i = 0; i < links.size() && links[i]->lable != lable; i++);
	for (int li = 0; li < links[i]->links.size(); li++)cout << links[i]->links[li]->lable << "";
	cout << endl;
}//adjacent

string DFSH(const Node* a, string str) {
	size_t found = str.find(a->lable);
	if (found == string::npos) {
		str += a->lable;
		for (int i = 0; i < a->links.size(); i++) {
			str = DFSH(a->links[i], str);
		}
		cout << a->lable << " ";
	}
	return str;
}//DFS helper

void DFS(const vector<Node*>& vec, const char letter) {
	int i;
	for (i = 0; vec[i]->lable != letter; i++);
	string str = "";
	str += letter;
	for (int j = 0; j < vec[i]->links.size(); j++) {
		str = DFSH(vec[i]->links[j], str);
	}

}//DFS
string connectedh(Node* a, string str) {
	size_t found = str.find(a->lable);
	if (found == string::npos) {
		str += a->lable;
		for (int i = 0; i < a->links.size(); i++) {
			str = connectedh(a->links[i], str);
		}
	}
	return str;
}//connected helper

void connected(const vector<Node*>& vect) {
	int s = vect.size();
	string str = "";
	for (int i = 0; i < s; i++) {
		str = "";
		if (connectedh(vect[i], str).size() != s) {
			cout << "FALSE" << endl;
			return;
		}
	}
	cout << "TRUE" << endl;
}

bool contains(char c, string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == c) {
			return true;
		}
	}
	return false;
}//checks if char is in a string

void BFS(const vector<Node*>& vect, const char letter) {
	int i;
	string str = "";
	str += letter;
	vector<Node*> q;
	for (i = 0; vect[i]->lable != letter; i++);
	Node* r = vect[i];
	for (int j = 0; j < r->links.size(); j++) {
		q.push_back(r->links[j]);
	}

	for (int j = 0; j < q.size(); j++) {
		cout << q[j]->lable << " ";
		str += q[j]->lable;
		for (int l = 0; l < q[j]->links.size(); l++) {
			if (!contains(q[j]->links[l]->lable, str)) {
				q.push_back(q[j]->links[l]);
			}
		}
	}
}//BFS

int main()
{
	string i;
	cout << "file name: ";
	cin >> i;

	ifstream ifile(i); //pre-req file is weighted diagraph representation
	vector<Node*> allofem;
	char c;
	for (string line; getline(ifile, line); )
	{
		char c = line[0];
		int ni;
		for (ni = 0; ni < allofem.size() && allofem[ni]->lable != c; ni++);
		if (ni == allofem.size()) {
			Node* tmp = new Node;
			tmp->lable = c;
			allofem.push_back(tmp);
		}
		for (int i = 4; i < line.size() - 1; i += 4) {
			int li;
			for (li = 0; li < allofem[ni]->links.size() && allofem[ni]->links[li]->lable != line[i]; li++);
			if (li == allofem[ni]->links.size()) {
				char lc = line[i];
				int li2;
				for (li2 = 0; li2 < allofem.size() && allofem[li2]->lable != lc; li2++);
				if (li2 == allofem.size()) {
					Node* tmp2 = new Node;
					tmp2->lable = lc;
					allofem.push_back(tmp2);
				}
				allofem[ni]->links.push_back(allofem[li2]);
				allofem[ni]->weights.push_back(line[i + 2] - 48);
			}
			else {
				allofem[ni]->weights[li] = line[i + 2] - 48;
			}
		}
	}
	cout << "command file name: ";
	cin >> i;

	ifstream ifile2(i);
	string str;
	while (!ifile2.eof())
	{
		ifile2 >> str;
		cout << endl << endl << str << " ";
		if (str != "CONNECTED") {
			ifile2 >> c;
			cout << c << endl;
			if (str == "ADJACENT") {
				adjacent(allofem, c);
			}
			if (str == "DFS") {
				DFS(allofem, c);
			}
			if (str == "BFS") {
				BFS(allofem, c);
			}
		}
		else {
			cout << endl;
			connected(allofem);
		}
	}
}