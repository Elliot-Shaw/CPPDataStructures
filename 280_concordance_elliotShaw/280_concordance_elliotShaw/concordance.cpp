#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "concordance.h"
using namespace std;

struct Node {
	string word;
	Node* next;
};

struct AZNode {
	AZNode* next;
	Node* branch;
	char letter;
};

concordance::concordance() {
	top = bottom = nullptr;
	for (char lttr = 'a'; lttr <= 'z'; lttr++) {
		AZNode* p = new AZNode;
		p->letter = lttr;
		p->branch = nullptr;
		if (top == nullptr && bottom == nullptr) {
			top = bottom = p;
			p->next = nullptr;
		}
		else {
			p->next = nullptr;
			bottom->next = p;
			bottom = p;
		}
	}
}//constructor

concordance::concordance(string file) {
	concordance();
	createFrom(file);
}//overloaded constructor

void concordance::createFrom(string file) {
	ifstream theText;
	theText.open(file);
	if (theText) {
		string word;
		while (theText >> word) {
			// this block takes the word and removes non-letter characters from the front and back
			// then makes all letters lowercase in the word.
			while (true) {
				if (word.size() == 0) break;
				char b = word.back();
				char f = word.front();
				if (b < 'A' || (b > 'Z' && b < 'a') || b > 'z') {
					word.pop_back();
					continue;
				}
				if (f < 'A' || (f > 'Z' && f < 'a') || f > 'z') {
					word.erase(0, 1);
					continue;
				}
				break;
			}// remove bad end characters
			for (unsigned i = 0; i < word.length(); i++) { //I got an error here fixed by unsigned instead of int, why?
				if (word[i] < 'A' || (word[i] > 'Z' && word[i] < 'a') || word[i] > 'z') continue;
				if (word[i] >= 'A' && word[i] <= 'Z') word[i] += 32;
			}// make lowercase unless it is a dash or apostrophy or mid-word character (e.g. can't)

			if (word.size() == 0) continue; // this in case of string with all odd characters proccessed

			//put the word into the concordance
			AZNode* runner = top;
			int flag = 0;
			do {
				if (runner->letter == word[0]) {
					Node* runnerTwo = runner->branch;
					Node* prevPointer = runnerTwo;
					int flagTwo = 0;
					do {
						if (runnerTwo == nullptr) {
							Node* toInsert = new Node;
							toInsert->word = word;
							toInsert->next = nullptr;
							runner->branch = toInsert;
							break;// flagTwo = 1;
						}
						else if (runnerTwo->word == word) {
							break;// flagTwo = 1;
						}
						else if (runnerTwo->next == nullptr) {
							Node* toInsert = new Node;
							toInsert->word = word;
							if (word > runnerTwo->word) {
								toInsert->next = nullptr;
								runnerTwo->next = toInsert;
							}
							else {
								if (prevPointer == runner->branch) {
									toInsert->next = runner->branch;
									runner->branch = toInsert;
								}
								else {
									toInsert->next = prevPointer->next;
									prevPointer->next = toInsert;
								}
							}
							break;// flagTwo = 1;
						}
						else if (runnerTwo == runner->branch && word < runnerTwo->word) {
							Node* toInsert = new Node;
							toInsert->word = word;
							toInsert->next = runner->branch;
							runner->branch = toInsert;
							break;// flagTwo = 1;
						}
						else if ((runnerTwo->word < word) && (runnerTwo->next->word > word)) {
							Node* toInsert = new Node;
							toInsert->word = word;
							toInsert->next = runnerTwo->next;
							runnerTwo->next = toInsert;
							break;// flagTwo = 1;
						}
						else {
							prevPointer = runnerTwo;
							runnerTwo = runnerTwo->next;
						}
					} while (true);//flagTwo == 0);
					flag = 1;
				}
				else runner = runner->next;
			} while (flag == 0);
		}
	}

	theText.close();
}//createFrom

bool concordance::existanceOf(string word) {
	AZNode* runner = top;
	int flag = 0;
	while(true) {
		if (runner->letter == word[0]) {
			Node* runnerTwo = runner->branch;
			while (true) {
				if (runnerTwo == nullptr) {
					return false;
				}
				else if (runnerTwo->word == word) {
					return true;
				}
				else if (runnerTwo->word > word) {
					return false;
				}
				else {
					runnerTwo = runnerTwo->next;
				}
			} while (true);
		}
		else {
			runner = runner->next;
			if (runner == nullptr) {
				break;
			}
		}
	}
	return false;
}//existanceOf

void concordance::display(char letter) {
	AZNode* runner = top;
	cout << left;
	do {
		if (runner->letter == letter) {
			cout << char(runner->letter - 32) << ":" << endl;
			Node* runnerTwo = runner->branch;
			int space = 0;
			while (runnerTwo != nullptr) {
				if (space % 3 < 2) {
					cout << left << setw(15) << runnerTwo->word;
					space++;
				}
				else {
					cout << left << setw(15) << runnerTwo->word << endl;
					space++;
				}
				runnerTwo = runnerTwo->next;
			}
			if (space % 3 < 1) { cout << endl; }
			else { cout << endl << endl; }
			break;
		}
		else runner = runner->next;
	} while (runner != nullptr);
} //display (concordance of specific letter)

void concordance::display() {
	AZNode* runner = top;
	cout << left;
	do {
		cout << char(runner->letter - 32) << ":" << endl;
		Node* runnerTwo = runner->branch;
		int space = 0;
		while (runnerTwo != nullptr) {
			if (space % 3 < 2) {
				cout << left << setw(15) << runnerTwo->word;
				space++;
			}
			else {
				cout << left << setw(15) << runnerTwo->word << endl;
				space++;
			}
			runnerTwo = runnerTwo->next;
		}
		if (space % 3 < 1) { cout << endl; }
		else { cout << endl << endl; }
		runner = runner->next;
	} while (runner != nullptr);
} //display (entire concordance)