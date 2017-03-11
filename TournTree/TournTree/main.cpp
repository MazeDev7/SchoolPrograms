/* MinBin

This program takes a number of packages and sorts them
into bins based in first fit order. If there is no room
in the first bin, it will move to the next available bin
using the binary tree algorithm by comparing the upper most
internal nodes and moving down.The internal nodes hold the highest value of the two bins
beneath them. The algorithm will traverse down the tree to find the first fit, then
traverse back up the tree and update all the internal nodes
with the latest highest values. The binary tree algorithm
takes the time placement of the packages into the bins from
a linear function of O(n), to an logarithmic function of O(lg(n)).
Lastly, the capacity of the bins will be printed to the screen.
The user will have the option of running multiple cases.


Created by Ali Mazeh on 6/4/16.
Copyright (c) 2016 Ali Mazeh. All rights reserved.
*/

#include <iostream>
#include <vector>

using namespace std;

// Initialize structure for tournament tree nodes
struct TournNode {

	/*Pre:
	* [in] cap - must be >= 0
	* [in] *p
	* [in] *lf
	* [in] *rt
	Post:
	* Initializes default values to variables and pointers in struct
	*/
	// Default constructor
	TournNode(int cap = 0, TournNode *p = nullptr, TournNode *lf = nullptr, TournNode *rt = nullptr)
		:data(cap), left(lf), right(rt), parent(p) {}

	// Declare variables and pointers
	int data;
	TournNode *parent;
	TournNode *right;
	TournNode *left;
};

// Initialize tournament tree class
class TournTree {
public:
	/*Pre:
	* Nothing
	Post:
	* Initializing default constructor
	*/
	// Default constructor
	TournTree() {}

	/*Pre:
	* [in] package - hold the size of the current package
	* package must be <= maxSize and >= 0
	Post:
	* The available size of the found bin is subtracted by the size of package
	*/
	// Class function that places an item of size package into first fit bin
	void add2Bin(int package) {
		// Set / reset currNode to point to the root node in the internal tree
		currNode = internal[1];
		currNode->left = internal[1]->left;
		currNode->right = internal[1]->right;

		// Loop to traverse down the tree until you reach a terminal node
		while ((currNode->left != nullptr && currNode->right != nullptr) || (currNode->left != nullptr && currNode->right == nullptr)) {

			// Compare package size to the node on the left side
			// If smaller, then currNode will now be that node
			if (package <= currNode->left->data)
				currNode = currNode->left;
			// If not smaller than the node on the left, then package
			// belongs on the right side. So node will become node to the right
			else
				currNode = currNode->right;
		}
		// When loop is done, currNode will equal the first fit bin
		// Subtract the the package size from the current bin size
		currNode->data -= package;
	}

	/*Pre:
	* [in] binIndex - holds the index number of the last used bin
	*  binIndex - must be >0 and <= numItems
	Post:
	* The parent nodes of the internal tree starting from avail[binIndex] and moving up
	* until hitting nullptr, are updated to the largest number of the node to its left or right
	*/
	// Class function that updates tree using index binIndex as starting point
	void updateTree(int binIndex) {
		// currNode is already pointing to the last changed bin
		// so just let it point to that bins parent and start traversing up
		// from there. No getIndex function required. Laziness #ftw
		currNode = currNode->parent;

		// Loop to traverse up the tree while the currNode does not equal nullptr
		while (currNode != nullptr) {
			// If currNode right is equal to nullptr(for odd bins)
			if (currNode->right == nullptr)
				//  Then currNode can only equal value of left node
				currNode->data = currNode->left->data;
			// Else, compare if left node data is bigger than right node data
			else if (currNode->left->data > currNode->right->data)
				// If true, set current node as that data
				currNode->data = currNode->left->data;
			else
				// Else, largest data of both must be right
				currNode->data = currNode->right->data;

			// currNode equals its parent and moves up the tree
			currNode = currNode->parent;
		}
	}

	/*Pre:
	* [in] numItems - contains number of items/bins. Must be >0
	* [in] size - contains max size of each bin. Must be >0
	Post:
	* Starting from root, attaches each node to its proper *left and *right node
	* When all internal nodes are attached, attaches terminal nodes to the proper bins
	*/
	// Class function that creates the internal nodes of the binary tree
	void makeInternal(int numItems, int size) {
		// Initialize variables , reset binIterator
		int iterator = 1, nodeCount = 1, binIterator = 1, loopIt;

		// allocate memory for the nodes by using .resize() member function
		internal.resize(numItems + 1);
		// allocate memory for the queue size by using .resize() member function
		terminalQueue.resize(((numItems + 1) / 2) + 1);

		// loop and use new to create dynamic memory of TournNode with max capacity
		for (int i = 1; i< numItems + 1; i++)
			internal[i] = new TournNode(size);

		// Test if number of bins is even or odd to get right loop counter
		if (numItems % 2 == 0)
			loopIt = numItems / 2;
		else
			loopIt = (numItems / 2) + 1;

		// loop and attach children to parents for number of bins
		for (int i = 1; i< loopIt; i++) {
			// internal[i] is the parent of internal[2*i] and internal[2*i+1]
			// Attach current node to the node to its left
			internal[i]->left = internal[2 * i];
			// Attach current node as the parent to the node to its left
			internal[i]->left->parent = internal[i];
			// Iterate to keep track of number of nodes placed
			nodeCount++;

			// If number of nodes placed is equal to number of items
			// then the limit of internal nodes has been reached and break out of the loop
			// to avoid bad access exception flag
			if (nodeCount == numItems)
				break;

			// Attach current node to the node to its right
			internal[i]->right = internal[(2 * i) + 1];
			// Set the current bins parent to point to the node directly above it
			internal[i]->right->parent = internal[i];
			// Iterate to keep track of number of nodes placed
			nodeCount++;
		}
		// Set currNode equal to the first/root node of internal nodes
		currNode = internal[1];
		// Call function to fill a queue of all terminal nodes
		fillQueue(currNode, numItems);

		// Loop through terminalQueue to attach bins
		for (int i = 1; i< (avail.size() / 2) + 1; i++) {
			// Check to make sure iterator does not surpass size of actual vector
			// to avoid bad access exception
			if (iterator < avail.size()) {
				// Set the current terminal nodes left to point to the first bin
				terminalQueue[i]->left = avail[iterator];
				// Set the current bins parent to point to the node directly above it
				avail[iterator]->parent = terminalQueue[i];
				// iterate to move to the next bin
				iterator++;
			}
			// Check to make sure iterator does not surpass size of actual vector
			// to avoid bad access exception
			if (iterator < avail.size()) {
				// Set the current terminal nodes right to point to the next bin
				terminalQueue[i]->right = avail[iterator];
				// Set the current bins parent to point to the node directly above it
				avail[iterator]->parent = terminalQueue[i];
				// iterate to move to the next bin
				iterator++;
			}
		}
	}

	/*Pre:
	* [in] *newRoot -contains pointer to first/root node of internal tree
	* [in] numItems - contains number of items/bins. Must be >0
	Post:
	* [modified] fillQueue - recursive function that fills a vector with all terminal nodes
	* in order from left to right in a binary tree using pre-order depth first search
	*/
	void fillQueue(TournNode *newRoot, int numItems) {
		// Base case - return if root is equal to nullptr
		if (newRoot == nullptr)
			return;
		// If roots left and roots right is equal to nullptr, then root is a terminal node
		if (newRoot->left == nullptr && newRoot->right == nullptr) {
			// Set current position of terminalQueue[binIterator] to equal the current address of newRoot
			terminalQueue[binIterator] = newRoot;
			// Iterate to move the terminal vector to the next spot
			binIterator++;
		}
		// Call function recursively for pre-order traversal
		fillQueue(newRoot->left, numItems);
		fillQueue(newRoot->right, numItems);
	}

	/*Pre:
	* [in] numItems - hold number of items/bins. Must be >0
	* [in] size - holds number of maximum capacity per bins
	Post:
	* allocates new memory in each index of avail vector to be used as bins
	*/
	// Class function to initialize dynamic memory for bins to be stored
	void createBins(int numItems, int size) {
		// Resize bin vector to size of numItems+1(first memory location will be unused)
		avail.resize(numItems + 1);

		// Loop through vector
		for (int i = 1; i < numItems + 1; i++)
			// At every vector spot, create dynamic memory
			avail[i] = new TournNode(size);
	}

	/*Pre:
	* [in] numItems - hold number of items/bins. Must be >0
	* [in] size - holds number of maximum capacity per bins
	Post:
	* Prints contents of vector to the screen
	*/
	// Class function to print out the contents of the bins
	void printBins(int numItems, int maxSize) {
		// Loop through vector
		for (int i = 1; i<avail.size(); i++) {
			// If data at index of vector is equal to max capacity, don't print
			// else, print
			if (avail[i]->data != maxSize) {
				cout << avail[i]->data << " ";
			}
		}
		cout << endl;
	}

private:
	// Declare vectors and nodes
	TournNode * currNode;
	vector< TournNode * > internal;
	vector< TournNode * > avail;
	vector< TournNode * > terminalQueue;
	int binIterator = 1;
};

int main() {

	// Declare variables
	int testCases, numItems, maxSize, package, index;

	// Read in number of test cases
	cin >> testCases;

	// Loop the proogram per number of test
	for (int i = 0; i < testCases; i++) {

		// Read in number of bins/items and max capacity of all bins
		cin >> numItems >> maxSize;

		// Initialize TournTree object member
		TournTree umd;
		// Call function to allocate memory for the new bins
		umd.createBins(numItems, maxSize);
		// Call function to create the internal nodes of the binary tree
		umd.makeInternal(numItems, maxSize);

		// Loop for each new package received
		for (int j = 0; j<numItems; j++) {

			// Read in package size to be placed in bins
			cin >> package;
			// Call function to send package size and add it to the proper bin
			umd.add2Bin(package);
			// Call function which will use the index of the last bin used to update the tree
			umd.updateTree(index);
		}

		// Call function to print out the size of all the bins in order
		umd.printBins(numItems, maxSize);
	}
	return 0;
}
