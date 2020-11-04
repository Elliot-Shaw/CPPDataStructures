/*
280
Arrays
Elliot Shaw
 */

#include "pch.h" //Why is this default in VS? Without it it won't compile, but I don't use it either. 
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void load(int x[], int y)
{
	for (int i = 1; i <= y; i++) {
		cout << "enter integer " << i << ": ";
		cin >> x[i - 1];
		cout << endl;
	}
}//load
void display(int x[], int y) 
{
	cout << "\nNumbers in the array: ";
	for (int i = 1; i <= y; i++) {
		cout << x[i - 1] << "  ";
	}
	cout << endl;
}//display
int get(int x[], int y)
{
	return x[y-1];
}//get
void set(int x[], int y, int z)
{
	x[y - 1] = z;
}//set
void deleet(int x[], int &y, int z) 
{	
	int hold;
	for (int i = y; i > z; i--) {
		hold = x[i - 2];
		x[i - 2] = x[y - 1];
		x[y - 1] = hold;
	}
	x[y-1] = 0;
	y--;
}//delete
void insert(int x[], int &y, int z, int t) 
{
	int hold;
	int flag = 0;
	for (int i = z; i <= y+1; i++) {
		if (flag == 0) {
			hold = x[z - 1];
			x[i - 1] = t;
			flag = 1;
		}
		else {
			int a = x[i-1]; 
			x[i - 1] = hold;
			hold = a;
		}
	}
	y++;
}//insert
double findAve(int x[], int y)
{
	int total = 0;
	for (int i = 1; i <= y; i++) {
		total = total + x[i - 1];
	}
	return ((1.0*total) / (1.0*y));
}//Find Average
int findMin(int x[], int y)
{
	int current;
	int flag = 0;
	for (int i = 1; i <= y; i++) {
		if (flag == 0) {
			current = x[i - 1];
			flag = 1;
		}
		if (x[i - 1] < current) {
			current = x[i - 1];
		}
	}
	return current;
}//Find Min
void sort(int x[], int y) 
{
	int check = 1;
	do {
		check = 0;
		for (int i = 1; i < y; i++) {
			if (x[i - 1] > x[i]) {
				int a = x[i];
				x[i] = x[i - 1];
				x[i - 1] = a;
			}
		}
		for (int i = 1; i < y; i++) {
			if (x[i - 1] > x[i]) {
				check = 1;
			}
		}
	} while (check == 1);
}//Sort
int main()
{
	int theList[10]{ 0,0,0,0,0,0,0,0,0,0 };
	int count = 0;
	char leave = 'n';
	int choice = 0;

	do {


		cout << "Choose options from the menu below\n\n " << endl;
		cout << left;

		//Sets gives options to work with the array
		cout << setw(6) << "1" << "load" << endl;
		cout << setw(6) << "2" << "display" << endl;
		cout << setw(6) << "3" << "get" << endl;
		cout << setw(6) << "4" << "set" << endl;
		cout << setw(6) << "5" << "delete" << endl;
		cout << setw(6) << "6" << "insert" << endl;
		cout << setw(6) << "7" << "findMin" << endl;
		cout << setw(6) << "8" << "findAve" << endl;
		cout << setw(6) << "9" << "sort" << endl;
		cout << setw(6) << "10" << "exit" << endl << endl;

		cout << "option: ";
		cin >> choice;

		//Implements the options
		if (choice == 1) {
			cout << "How many integers do you want in the function? (10 integers max)  ";
			cin >> count;
			load(theList, count);
		}//load
		else if (choice == 2) {
			display(theList, count);
		}//display
		else if (choice == 3) {
			int temp;
			cout << "which element would you like to get? ";
			cin >> temp;
			if (temp > count || temp < 1) {
				cout << "Element " << temp << " does not exist in the array" << endl;
			}
			else {
				cout << "Element " << temp << " in the array is " << get(theList, temp) << endl;
			}
		}//get
		else if (choice == 4) {
			int temp;
			cout << "Which element in the array would you like to change? ";
			cin >> temp;
			cout << endl;
			if (temp > count || temp < 1) {
				cout << "That is not a valid element in the array" << endl;
			}
			else {
				int change;
				cout << "what would you like to change element " << temp << " to? ";
				cin >> change;
				set(theList, temp, change);
				display(theList, count);
			}
		}//set
		else if (choice == 5) {
			int temp;
			cout << "Which element would you like to delete? ";
			cin >> temp;
			cout << endl;
			if (temp > count || temp < 1) {
				cout << "That is not a valid element in the array" << endl;
			}
			else {
				deleet(theList, count, temp);
			}
			display(theList, count);
		}//delete
		else if (choice == 6) {
			if (count < 10) {
				int temp;
				cout << "Where would you like to insert an element? ";
				cin >> temp;
				cout << endl;
				if (temp > count+1 || temp < 1) {
					cout << "That is not a valid position in the array." << endl;
				}
				else {
					int replace;
					cout << "What would you like to put in element " << temp << "? ";
					cin >> replace;
					cout << endl;
					insert(theList, count, temp, replace);
					display(theList, count);
				}
			}
			else {
				cout << "The array is full, you may not insert any elements." << endl;
			}

		}//insert
		else if (choice == 7) {
			cout << "The minimum value in the array is: " << findMin(theList, count) << endl;
		}//Find Min
		else if (choice == 8) {
			cout << "The average value in the array is: " << findAve(theList, count) << endl;
		}//Find Average
		else if (choice == 9) {
			sort(theList, count);
			display(theList, count);
		}//Sort
		else if (choice == 10) {
			leave = 'y';
		}//Exit

		system("pause");
		cout << "\n\n\n\n\n" << endl;
		

	} while (leave != 'y');
}
