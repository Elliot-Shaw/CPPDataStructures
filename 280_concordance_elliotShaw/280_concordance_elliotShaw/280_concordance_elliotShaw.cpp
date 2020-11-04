#include <iostream>
#include <string>
#include <iomanip>
#include "concordance.h"

using namespace std;

int main() {
	char exit = 'n';
	int choice;
	do {
		cout << left;
		cout << "What would you like to do?" << endl << endl;
		cout << setw(3) << "1" << setw(3) << "-" << "Display concordance" << endl;
		cout << setw(3) << "2" << setw(3) << "-" << "Display letter of concordance (A-Z)" << endl;
		cout << setw(3) << "3" << setw(3) << "-" << "Find Word" << endl;
		cout << setw(3) << "4" << setw(3) << "-" << "Exit" << endl << endl;

		cin >> choice;

		while (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> choice;
		}

		concordance gettysburg;
		gettysburg.createFrom("resume.txt");

		if (choice == 1) {
			cout << endl;
			gettysburg.display();
			cout << endl;

			cin.ignore();
		}
		else if (choice == 2) {
			char character;
			cout << "Choose a letter A-Z: ";
			cin >> character;

			while (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> character;
			}

			cout << endl;

			gettysburg.display(character);

		}
		else if (choice == 3) {
			string word;
			cout << "What word would you like to know is in the concordance?: ";
			cin >> word;

			while (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> word;
			}

			cout << endl;

			if (gettysburg.existanceOf(word) == 1) {
				cout << word << " is in the concordance" << endl << endl;
			}
			else {
				cout << word << " is not in the concordance" << endl << endl;
			}

		}
		else if (choice == 4) {
			exit = 'y';
		}
		else {
			cout << "That is not a choice try again." << endl;
		}
	} while (exit != 'y');
	return 0;
}