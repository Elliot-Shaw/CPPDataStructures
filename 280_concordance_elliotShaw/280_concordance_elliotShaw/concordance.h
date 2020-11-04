#ifndef SHAW_CONCORDANCE_H
#define SHAW_CONCORDANCE_H

using namespace std;

struct Node;

struct AZNode;

class concordance {
private:
	AZNode* top, * bottom;
public:
	concordance();
	concordance(string file);
	void createFrom(string file);
	bool existanceOf(string word);
	void display(char letter);
	void display();
};
#endif