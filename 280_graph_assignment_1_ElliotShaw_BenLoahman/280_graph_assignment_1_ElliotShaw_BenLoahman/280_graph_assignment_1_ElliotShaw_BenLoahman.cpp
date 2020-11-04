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
	vector<int> wieghts;
};

void adjacent(const vector<Node*>& links, const char lable) {
	for (int i = 0; i < links.size(); i++) {
		if (links[i]->lable == lable) {
			for (int j = 0; j < links[i]->links.size(); j++) {
				cout << links[i]->links[j]->lable << " ";
			}
			break;
		}
	}
}//adjacent

void DFS(const vector<Node*>& element, const char letter, string covered = "") {
	for (int i = 0; i < element.size(); i++) {
		if (element[i]->lable == letter) {
			size_t found = covered.find(letter);
			if (found == string::npos) {
				cout << letter << " ";
				covered += letter;
				for (int j = 0; j < element[i]->links.size(); j++) {
					DFS(element[i]->links[j]->links, element[i]->links[j]->lable, covered);
				}
			}
		}
	}
}//DFS

void BFS(const vector<Node*>& element, const char letter, string covered = "", string displayed = "") {
	size_t found = covered.find(letter);
	if (found == string::npos) {
		covered += letter;
		for (int i = 0; i < element.size(); i++) {
			if (element[i]->lable == letter) {
				found = displayed.find(letter);
				if (found == string::npos) {
					cout << letter << " ";
					displayed += letter;
				}

				for (int j = 0; j < element[i]->links.size(); j++) {
					found = displayed.find(element[i]->links[j]->lable);
					if (found == string::npos) {
						cout << element[i]->links[j]->lable << " ";
						displayed += element[i]->links[j]->lable;
					}
				}

				for (int j = 0; j < element[i]->links.size(); j++) {
					BFS(element[i]->links[j]->links, element[i]->links[j]->lable, covered, displayed);
				}
			}
		}
	}
}//BFS

bool connected(const vector<Node*>& element) {
	string theNodes = "";
	for (int i = 0; i < element.size(); i++) {
		theNodes += element[i]->lable;
	}

	size_t found;

	for (int i = 0; i < element.size(); i++) {
		for (int j = 0; j < element[i]->links.size(); j++){
			found = theNodes.find(element[i]->links[j]->lable);
			if (found == string::npos) {
				return false;
			}
		}
	}

	return true;
}//connected

int main()
{


	return 0;
}//main