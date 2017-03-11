/*
sets.cpp

This program allows a user to input multiple set functions
using the keyboard or a file. Up to 10 sets may be active at once.


Created by Ali Mazeh on 7/26/16.
Copyright (c) 2016 Ali Mazeh. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
// Struct for nodes to be used in linked list
struct Node {

	// Default constructor
	Node(char ele = NULL, Node *n = nullptr)
		:element(ele), next(n) {}

	// Declare variables
	char element;
	Node *next;
};

// Initialize class to be used which will hold main vector with linked lists
// along with functions for sets
class SetFunctions {
public:

	// Default constructor
	SetFunctions() {}

	// Resize function to allow vector to hold max of 10 active sets
	void resizeVector() { list.resize(10); }

	// Function to create an empty set, or if one already exists, clear out all the elements
	void makeNull(char setName)
	{   // Declare and initialize variables
		bool exists = false, room = false;
		int it = 0;
		// Loop to check if the given set previously exists
		// Check the first position in each vector list; Where the set name resides
		for (int i = 0; i<10; i++) {
			// Do nothing if position is nullptr
			if (list[i] != nullptr) {
				// If current element matches with set name, set previously exists.
				if (list[i]->element == setName) {
					exists = true;
					// Set iterator of current position to be used later
					it = i;
					break;
				}
			}
			// If set name cannot be found, but a nullptr has been found,
			// then there is room for an extra set
			else if (list[i] == nullptr) {
				room = true;
				it = i;
			}
		}
		// If set already exists, clear set of all elements.
		if (exists == true) {
			clearSet(it);

			cout << "Set " << setName << " previously existed. All elements have been removed." << endl;
		}
		// If set does not exist but there is room, create set.
		else if (exists == false && room == true) {
			list[it] = new Node;
			list[it]->element = setName;
			cout << "Set " << setName << " has been created and nullified." << endl;
		}
		// If set does not exist and there is no room, notify user.
		else
			cout << "Error! No more available space for sets. Max of 10 has been reached." << endl;
	}
	// Function to insert an element into a set.
	void insert(char member, char setName) {
		// Declare and Initialize variables.
		bool found = false, duplicate = false;
		int it = 0;
		Node *temp;
		// Loop through vector to check if set exists before doing any operations on it.
		for (int i = 0; i < 10; i++) {
			// If current position in vector is nullptr, skip to next position.
			if (list[i] == nullptr)
				continue;
			// If current element is equal to set name, the set exists.
			else if (list[i]->element == setName) {
				found = true;
				it = i;
				break;
			}
		}
		// Set temp pointer to point to the head of the specific set.
		temp = list[it];
		// Iterate throught the linked list to find if the member already exists
		// a set cannot hold duplicates.
		while (temp != nullptr) {
			if (temp->element == member)
				duplicate = true;
			temp = temp->next;
		}
		// If set cannot be found, notify user.
		if (found == false)
			cout << "Set " << setName << " does not exist." << endl;
		// If member already exists in set, notify user.
		else if (duplicate == true)
			cout << "Member " << member << " already exists in set " << setName << "." << endl;
		// If set exists and member cannot be found, insert member.
		else {
			// Set temp to point to the head of the set.
			temp = list[it];
			// Iterate through the list until reaching the tail of the list.
			while (temp->next)
				temp = temp->next;
			// After reaching the end of the list, add new member.
			temp->next = new Node(member);

			cout << "Member " << member << " has been inserted in set " << setName << "." << endl;
		}
	}
	// Function to print out a set
	void printSet(char setName) {
		// Declare and initialize variables.
		bool exist = false;
		int it = 0;
		Node *temp;
		// Loop through vector to check if set exists.
		for (int i = 0; i < 10; i++) {
			// If current position in vector is nullptr, skip to next position.
			if (list[i] == nullptr)
				continue;
			// If current element is equal to set name, the set exists.
			else if (list[i]->element == setName) {
				exist = true;
				it = i;
				break;
			}
		}
		// If set does not exist, notify user.
		if (exist == false)
			cout << "Set " << setName << " does not exist." << endl;
		// If set exists, print out members.
		else {
			// Set temp to point to the head of the set
			temp = list[it];
			cout << "Set " << setName << " { ";
			// Loop through set printing out members
			while (temp->next != nullptr) {
				temp = temp->next;
				cout << temp->element << " ";
			}
			cout << "}" << endl;
		}
	}
	// Function to delete a member of a set
	void deleteMember(char member, char setName) {
		// Declare and Initialize elements.
		Node *temp;
		Node *prev = nullptr;
		bool exist;
		int it = 0;
		// Loop through vector to check if set exists.
		for (int i = 0; i < 10; i++) {
			// If current position in vector is nullptr, skip to next position.
			if (list[i] == nullptr)
				continue;
			// If current element is equal to set name, the set exists.
			else if (list[i]->element == setName) {
				exist = true;
				it = i;
				break;
			}
		}
		// If set does not exist, notify user.
		if (exist == false)
			cout << "Set " << setName << " does not exist." << endl;

		else if (exist == true) {
			// Set temp to point to the head of the set
			temp = list[it];
			// Loop through set to find element in the linked list.
			while (temp->next != nullptr) {
				// If member is found, break out of loop
				if (temp->element == member)
					break;
				// If member not found at current position, set prev pointer to point to
				// the position directly before the current position
				prev = temp;
				// Move down list
				temp = temp->next;
			}
			// After member is found, if member is the tail of the list, remove the tail.
			if (temp->next == nullptr) {
				delete temp;
				prev->next = nullptr;

				cout << "Member " << member << " has been removed from set " << setName << "." << endl;
			}
			// If member is found between two members, change pointers and delete node.
			else {

				prev->next = temp->next;
				delete temp;

				cout << "Member " << member << " has been removed from set " << setName << "." << endl;
			}
		}
		// If member does not exist, notify user.
		else
			cout << "Member " << member << " does not exist in set " << setName << "." << endl;
	}
	// This function will be used to completely remove a set from the vector
	void destroySet(char setName) {
		// declare and initialize variables
		bool exist = false;
		int it = 0;
		Node *temp;
		// Loop through vector to check if set exists.
		for (int i = 0; i < 10; i++) {
			// If current position in vector is nullptr, skip to next position.
			if (list[i] == nullptr)
				continue;
			// If current element is equal to set name, the set exists.
			else if (list[i]->element == setName) {
				exist = true;
				it = i;
				break;
			}
		}
		// If set does not exist, notify user.
		if (exist == false)
			cout << "Set " << setName << " does not exist." << endl;
		else {
			// If set does exist, clear set.
			clearSet(it);
			// After clearing set, the head node remains. Remove the head node.
			temp = list[it];
			list[it] = nullptr;
			delete temp;

			cout << "Set " << setName << " has been removed." << endl;
		}
	}
	// Function to search for a member in all sets and print out the set it's located in.
	void findPrint(char member) {
		// Declare and initialize variables
		bool exist = false;
		int it = 0;
		Node *temp;
		char set;
		// Loop through vector to find set
		for (int i = 0; i < 10; i++) {
			if (list[i] == nullptr)
				continue;
			else {
				// After set has been found, set temp to point to head of set
				temp = list[i];
				// Iterate through set to see if member exists
				while (temp != nullptr) {
					if (temp->element == member) {
						it = i;
						exist = true;
					}
					// Iterate to next node
					temp = temp->next;
				}
			}
		}
		// If member and set exists, print out set that member belongs to
		if (exist == true) {
			set = list[it]->element;
			cout << "Member " << member << " was found in set " << set << "." << endl;

			printSet(set);
		}
		else
			// If member does not exist, notify user
			cout << "Member " << member << " does not exist." << endl;
	}
	// Function to copy elements of one set into another
	void assignSet(char set1, char set2) {
		// Declare and initialize variables
		Node *temp;
		bool exist = false, exist2 = false;
		int it = 0, it2 = 0;
		char setName, member;
		// Loop through vector to find if both sets exist
		for (int i = 0; i < 10; i++) {
			if (list[i] == nullptr)
				continue;

			if (list[i]->element == set1) {
				exist = true;
				it = i;
			}
			if (list[i]->element == set2) {
				exist2 = true;
				it2 = i;
			}
		}
		// If one of the sets does not exist, notify user.
		if (exist == false || exist2 == false)
			cout << "One of the sets does not exist" << endl;
		else {
			// If sets do exist, clear out second set.
			setName = list[it2]->element;
			// Call function to clear out second set
			clearSet(it2);
			// Set temp to point to the first member in the first set
			temp = list[it]->next;
			// Iterate through the set
			while (temp != nullptr) {
				member = temp->element;
				// Call function to insert every member from first set to second set
				insert(member, setName);
				temp = temp->next;
			}
		}
	}
	// Function to combine members of two sets and place the product in a third set
	void unionSet(char set1, char set2, char set3) {
		// Declare and initialize variables
		Node *temp;
		bool exist = false, exist2 = false, exist3 = false;
		int it = 0, it2 = 0, it3 = 0;
		char setName, member;
		// Loop to check if the sets exist
		for (int i = 0; i < 10; i++) {
			if (list[i] == nullptr)
				continue;

			if (list[i]->element == set1) {
				exist = true;
				it = i;
			}
			if (list[i]->element == set2) {
				exist2 = true;
				it2 = i;
			}
			if (list[i]->element == set3) {
				exist3 = true;
				it3 = i;
			}
		}
		// If one of the sets does not exist, notify the user.
		if (exist == false || exist2 == false || exist3 == false)
			cout << "One of the sets does not exist" << endl;
		else {
			// Set a variable to hold the name of the set that will contain the product
			setName = list[it3]->element;
			// If one of the two sets being combined is the same set that will contain the product,
			// do not clear the set
			if ((set1 != set3) && (set2 != set3))
				clearSet(it3);
			// Set temp to point to head of the first set
			temp = list[it]->next;
			// Iterate through set and insert all members into new set. Insert function will take care of duplicates
			while (temp != nullptr) {
				member = temp->element;
				insert(member, setName);
				temp = temp->next;
			}
			// Set temp to point to head of the second set
			temp = list[it2]->next;
			// Iterate through set and insert all members into new set. Insert function will take care of duplicates
			while (temp != nullptr) {
				member = temp->element;
				insert(member, setName);
				temp = temp->next;
			}
			cout << "Union of set " << set1 << " and set " << set2 << " is completed within set " << set3 << "." << endl;
		}
	}
	// Function will take the difference between two sets and place the product into a third set
	void difference(char set1, char set2, char set3) {
		// Declare and initialize variables
		Node *temp;
		Node *temp2;
		bool exist = false, exist2 = false, exist3 = false, duplicate = false, arrayOnTop = false;
		int it = 0, it2 = 0, it3 = 0, k = 0, j = 0;
		char setName, member, array[26] = {};
		// Loop through vector to see if sets exist
		for (int i = 0; i < 10; i++) {
			if (list[i] == nullptr)
				continue;
			if (list[i]->element == set1) {
				exist = true;
				it = i;
			}
			if (list[i]->element == set2) {
				exist2 = true;
				it2 = i;
			}
			if (list[i]->element == set3) {
				exist3 = true;
				it3 = i;
			}
		}
		// If one of the sets do not exist, notify user.
		if (exist == false || exist2 == false || exist3 == false)
			cout << "One of the sets does not exist" << endl;
		// Check if one of the two sets being added is the same set where the products are being placed
		else if ((set1 == set3) || (set2 == set3)) {
			// If true, then set k to hold the remaining sets position
			if (set1 == set3) {
				k = it2;
				// If the first set is the same set where the answers will be held,
				// the array holding the set member will be the top loop
				arrayOnTop = true;
			}
			else
				// If the second set is the set where the answers will be held, set k to hold the position of
				// the first set
				k = it;
			// Let setName hold the character name of the set
			setName = list[it3]->element;
			// temp will point to the frst member in the set where the answers will be stored
			temp = list[it3]->next;
			// Loop through the set and store the members in a temporary array that will hold the members of the set
			while (temp != nullptr) {
				array[j] = temp->element;
				temp = temp->next;
				j++;
			}
			// Clear the third set to give it room to hold the product
			clearSet(it3);
			// If true, then the temp array will be the outer loop.
			if (arrayOnTop == true) {
				// Inner loop which will go through linked list of other set
				for (int i = 0; i < j; i++) {
					temp = list[k];
					duplicate = false;
					// Compare all elements of second set to current element of first set
					while (temp != nullptr) {
						if (temp->element == array[i])
							duplicate = true;
						temp = temp->next;
					}
					// If a member in first set does not exist in second set, insert member to third set.
					if (duplicate == false)
						insert(array[i], setName);
				}
			}
			// If the array is not on top, it will be in the inner loop
			else {
				// temp will point to the first member in the first set
				temp = list[k]->next;
				// Loop through set
				while (temp != nullptr) {
					duplicate = false;
					// Use inner loop to iterate through entire array
					for (int i = 0; i <= j; i++) {
						// Compare members
						if (temp->element == array[i])
							duplicate = true;
					}
					// Set member to equal the character value of the member
					member = temp->element;
					// If a member in first set does not appear in second set, input that member to the the third set
					if (duplicate == false)
						insert(member, setName);
					// Iterate to next element in the first set
					temp = temp->next;
				}
			}

			cout << "Difference of set " << set1 << " and set " << set2 << " is completed within set " << set3 << "." << endl;
		}
		// If set 1 or set 2 is not equal to set 3, do this.
		else {
			// Let setName equal the character value of set
			setName = list[it3]->element;
			// Clear the set where the answers will be stored
			clearSet(it3);
			// temp will point to the first element in the set
			temp = list[it]->next;
			// loop through first set
			while (temp != nullptr) {
				// reset pointer back to begining of second set
				temp2 = list[it2];
				// reset flag
				duplicate = false;
				// Loop through second set
				while (temp2 != nullptr) {
					// Compare members in both sets
					if (temp->element == temp2->element)
						duplicate = true;
					// Iterate to next member in second set
					temp2 = temp2->next;
				}
				// Let member equal the character value of current member in first set
				member = temp->element;
				// If current member in first set doesnt appear in second set, input member to third set.
				if (duplicate == false)
					insert(member, setName);
				// Iterate to next member in first set
				temp = temp->next;
			}
			cout << "Difference of set " << set1 << " and set " << set2 << " is completed within set " << set3 << "." << endl;
		}
	}

	void intersection(char set1, char set2, char set3) {
		// Declare and initialize members
		Node *temp;
		Node *temp2;
		bool exist = false, exist2 = false, exist3 = false, duplicate = false;
		int it = 0, it2 = 0, it3 = 0, j = 0, k = 0;
		char setName, member, array[26] = {};
		// Loop to check if all the sets exist
		for (int i = 0; i < 10; i++) {
			if (list[i] == nullptr)
				continue;

			if (list[i]->element == set1) {
				exist = true;
				it = i;
			}
			if (list[i]->element == set2) {
				exist2 = true;
				it2 = i;
			}
			if (list[i]->element == set3) {
				exist3 = true;
				it3 = i;
			}
		}
		// If at least one of the sets do not exist, notify user
		if (exist == false || exist2 == false || exist3 == false)
			cout << "One of the sets does not exist" << endl;
		// Check if one of the two sets being compared is the same set where the answers
		// will be stored
		else if ((set1 == set3) || (set2 == set3)) {
			// If first set is the same set where the answers will be stored,
			// let k hold position value of the remaining set
			if (set1 == set3)
				k = it2;
			else
				k = it;
			// Let setName hold the character value of the set name
			setName = list[it3]->element;
			// temp will point to the first member in the third set
			temp = list[it3]->next;
			// Loop through set and store all members into an array
			while (temp != nullptr) {
				array[j] = temp->element;
				temp = temp->next;
				j++;
			}
			// Clear the set where the answers will be cleared
			clearSet(it3);
			// Loop through array to compare each member of array to each member of second set
			for (int i = 0; i < j; i++) {
				// Reset pointer to the begining of the list
				temp = list[k];
				// Reset flag
				duplicate = false;
				// Loop through second set
				while (temp != nullptr) {
					// Compare current member of first set to current member of second set
					if (temp->element == array[i])
						duplicate = true;
					// Iterate to next member in second set
					temp = temp->next;
				}
				// If you have a match, insert member to third set
				if (duplicate == true)
					insert(array[i], setName);
			}
			cout << "Intersection of set " << set1 << " and set " << set2 << " is completed within set " << set3 << "." << endl;
		}
		// If set1 or set2 does not equal set 3, do this
		else {
			// Let setName equal the character value of third set
			setName = list[it3]->element;
			// Clear third set
			clearSet(it3);
			// temp will point to first member in first set
			temp = list[it]->next;
			// Loop through first set
			while (temp != nullptr) {
				temp2 = list[it2];
				duplicate = false;
				// Loop through second set
				while (temp2 != nullptr) {
					if (temp->element == temp2->element)
						duplicate = true;
					temp2 = temp2->next;
				}
				member = temp->element;

				if (duplicate == true)
					insert(member, setName);
				temp = temp->next;
			}
			cout << "Intersection of set " << set1 << " and set " << set2 << " is completed within set " << set3 << "." << endl;
		}
	}
	// Function to clear out members from a set but leave head node which holds set name
	void clearSet(int it) {
		Node *temp;

		temp = list[it]->next;
		// Iterate through set deleting member nodes
		while (temp != nullptr) {
			list[it]->next = temp->next;
			temp->next = nullptr;
			delete temp;
			temp = list[it]->next;
		}
	}
	// Function to print all the active sets in memory. Will be used before termination.
	void finalPrint() {
		char setName;

		cout << "\nThe sets still existing before termination are: " << endl;
		// Iterate through vector, if current position is not empty, print set
		for (int i = 0; i < 10; i++) {
			if (list[i] != nullptr) {
				setName = list[i]->element;
				printSet(setName);
			}
		}
	}

private:
	// Vector of pointers that will hold up to 10 linked lists
	vector<Node *> list;

};

int main() {
	// Declare and initialize variables
	char choice;
	bool run = true;
	string input, fname;
	char var1, var2, var3;
	// Initialize input file stream
	ifstream ins;
	// Find out which type of input the user wants
	cout << "Keyboard input? If no, file input will proceed. (y/n):" << endl;
	cin >> choice;

	if (choice != 'y') {
		cout << "Enter filename: ";
		cin >> fname;
		// open requested filename
		ins.open(fname.c_str());
	}
	// Initialize class object
	SetFunctions init;
	// Call class function using class object
	init.resizeVector();
	// Loop until user enters EXIT
	do {
		// Recieve command/function
		if (choice == 'y')
			cin >> input;
		else {
			ins >> input;
			cout << input << " ";
		}
		// Proceed to match the command/function to the following options
		if (input == "EXIT") {
			init.finalPrint();
			cout << "Program ending." << endl;
			run = false;
		}

		if (input == "MAKENULL") {

			if (choice == 'y')
				cin >> var1;
			else {
				ins >> var1;
				cout << var1 << endl;
			}
			init.makeNull(var1);
		}

		if (input == "INSERT") {
			if (choice == 'y')
				cin >> var1 >> var2;
			else {
				ins >> var1 >> var2;
				cout << var1 << " " << var2 << endl;
			}
			init.insert(var1, var2);
		}

		if (input == "PRINTSET") {
			if (choice == 'y')
				cin >> var1;
			else {
				ins >> var1;
				cout << var1 << endl;
			}
			init.printSet(var1);
		}

		if (input == "DELETE") {
			if (choice == 'y')
				cin >> var1 >> var2;
			else {
				ins >> var1 >> var2;
				cout << var1 << " " << var2 << endl;
			}
			init.deleteMember(var1, var2);
		}

		if (input == "DESTROY") {
			if (choice == 'y')
				cin >> var1;
			else {
				ins >> var1;
				cout << var1 << endl;
			}
			init.destroySet(var1);
		}

		if (input == "FINDPRINT") {
			if (choice == 'y')
				cin >> var1;
			else {
				ins >> var1;
				cout << var1 << endl;
			}
			init.findPrint(var1);
		}

		if (input == "ASSIGN") {
			if (choice == 'y')
				cin >> var1 >> var2;
			else {
				ins >> var1 >> var2;
				cout << var1 << " " << var2 << endl;
			}
			init.assignSet(var1, var2);
		}

		if (input == "UNION") {
			if (choice == 'y')
				cin >> var1 >> var2 >> var3;
			else {
				ins >> var1 >> var2 >> var3;
				cout << var1 << " " << var2 << " " << var3 << endl;
			}
			init.unionSet(var1, var2, var3);
		}

		if (input == "DIFFERENCE") {
			if (choice == 'y')
				cin >> var1 >> var2 >> var3;
			else {
				ins >> var1 >> var2 >> var3;
				cout << var1 << " " << var2 << " " << var3 << endl;
			}
			init.difference(var1, var2, var3);
		}

		if (input == "INTERSECTION") {
			if (choice == 'y')
				cin >> var1 >> var2 >> var3;
			else {
				ins >> var1 >> var2 >> var3;
				cout << var1 << " " << var2 << " " << var3 << endl;
			}
			init.intersection(var1, var2, var3);
		}

	} while (run == true);

	return 0;
}