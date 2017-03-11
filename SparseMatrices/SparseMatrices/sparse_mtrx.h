/*
Ali H. Mazeh
02/1/2016

This program creates a dynamic array of linked list to hold the
non-zero elements of a matrix. This program provides operations
such as: Addition, subtraction, multiplication, and transposing of
sparse matrices.

*/
#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

struct Element
{
	int     col;
	double  value;
	Element *next;

	/*Pre:
	* [in] cols - column number with default value = -1, if another is not specified
	* [in] vals - value in column "cols"  with default value = 0, if another is not specified
	Post:
	* [out] void
	* [modified] "col", "value", "next" are updated
	*/
	Element(int c = -1, double val = 0, Element * ptr = NULL)
	{
		col = c;
		value = val;
		next = ptr;
	}

	/*Pre:
	* [in] val - value for the current column to be assigned
	Post:
	* [out] void
	* [modified] "value" is updated
	*/
	void operator=(double vals)
	{
		value = vals;
	}

	friend ostream& operator<<(ostream &out, Element ele);
};

/*Pre:
* [in] out - reference to the output stream for pringing data
* [in] ele   - "Element" to be printed
Post:
* [out] reference to "out" stream
*/
ostream& operator<<(ostream &out, Element rhs)
{
	out << rhs.value;
	return out;
}

class ElementList
{

private:
	Element *list; // pointer to the first (head) element of the linked list
	int maxCols; // maximum numbers of "columns" in linked list

public:

	// Constructor by default
	/*Pre:
	* [in] max - maxium nubmer of columns in the linked lists. Default value is zero, if another is not specified
	Post:
	* [out] void
	* [modified] "maxCols" is assigned to "max". Allocated memory for "list"
	*/
	ElementList(int maxC = 0)
	{
		maxCols = maxC;
		list = new Element();
	}

	// Destructor for cleaning memory
	/*Pre:
	* [in]
	* [var] Element *tmp, tmp2 are used as iterators to go through linked list
	Post:
	* [out] void
	* [modified] Memory taken by "list" is free
	*/
	~ElementList()
	{
		// Deletes elements one by one starting from the head element
		Element *tmp = list->next;
		Element *tmp2;

		while (tmp)
		{
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		list->next = NULL;
		delete list;
		delete tmp;
	}

	// Copy constructor
	/*Pre:
	* [in] rhs - reference to instance to be copied
	Post:
	* [out] void
	* [modified] "maxCol", "list" are updated in operator=
	*/
	ElementList(const ElementList &rhs)
	{
		operator=(rhs);
	}

	// Overloaded assigment operator with deep copy
	/*Pre:
	* [in] rhs - reference to instance to be copied
	* [var] Element *tmp is used as iterator
	Post:
	* [out] void
	* [modified] "maxCol", "list" are updated
	*/
	ElementList& operator=(const ElementList &rhs)
	{
		Element *tmp;

		if (this == &rhs)
			return *this;

		maxCols = rhs.maxCols;
		list = new Element();

		tmp = new Element();
		tmp = rhs.list;

		while (tmp->next)
		{
			tmp = tmp->next;
			add(tmp->col, tmp->value);
		}

		return *this;
	}

	// Overloaded operator for summation two linked lists
	/*Pre:
	* [in] rhs - reference to the instance to be added
	* [var] Element *tmp is used as iterator to rhs
	* [var] Element *head is used as iterator to this
	Post:
	* [out] result of summation this + rhs
	* [modified] nothing
	*/
	ElementList operator+(const ElementList &rhs)
	{
		// If lists have different sizes then assert
		if (maxCols < rhs.maxCols) assert(0);

		ElementList sum(maxCols);
		Element *tmp = new Element();
		Element *head = new Element();

		tmp = rhs.list;
		head = list;

		tmp = tmp->next;
		head = head->next;

		while (tmp && head)
		{
			if (tmp->col == head->col)
			{
				sum.add(tmp->col, head->value + tmp->value);
				tmp = tmp->next;
				head = head->next;
			}
			else if (tmp->col < head->col) // If columns are different
			{
				sum.add(tmp->col, 0.0 + tmp->value);
				tmp = tmp->next;
			}
			else if (tmp->col > head->col) // If columns are different
			{
				sum.add(head->col, head->value + 0.0);
				head = head->next;
			}
		}

		// if tmp list is not empty then continue to sum elements
		while (tmp)
		{
			sum.add(tmp->col, 0.0 + tmp->value);
			tmp = tmp->next;
		}

		// if head list is not empty then continue to sum elements
		while (head)
		{
			sum.add(head->col, head->value + 0.0);
			head = head->next;
		}

		return sum;
	}

	// The same as function above, only subtraction
	/*Pre:
	* [in] rhs - reference to the instance to be added
	* [var] Element *tmp is used as iterator to rhs
	* [var] Element *head is used as iterator to this
	Post:
	* [out] result of summation this + rhs
	* [modified] nothing
	*/
	ElementList operator-(const ElementList &rhs)
	{
		if (maxCols < rhs.maxCols) assert(0);

		ElementList sum(maxCols);
		Element *tmp = new Element();
		Element *head = new Element();

		tmp = rhs.list;
		head = list;

		tmp = tmp->next;
		head = head->next;

		while (tmp && head)
		{
			if (tmp->col == head->col)
			{
				sum.add(tmp->col, head->value - tmp->value);
				tmp = tmp->next;
				head = head->next;
			}
			else if (tmp->col < head->col)
			{
				sum.add(tmp->col, -tmp->value);
				tmp = tmp->next;
			}
			else if (tmp->col > head->col)
			{
				sum.add(head->col, head->value);
				head = head->next;
			}
		}

		while (tmp)
		{
			sum.add(tmp->col, -tmp->value);
			tmp = tmp->next;
		}

		while (head)
		{
			sum.add(head->col, head->value);
			head = head->next;
		}

		return sum;
	}

	// Adds element with value "val" to the column "col"
	/*Pre:
	* [in] col - column number to be added
	* [in] val - value of element in column "col"
	* [var] Element *tmp, *last are used as iterator to find right position in sorted list
	Post:
	* [out] void
	* [modified] list variable is updated
	*/
	void add(int col, double val)
	{
		// Check boundaries:
		//if (maxCols < col + 1) assert(0);
		Element * last;
		Element *tmp = new Element(col, val);
		tmp->next = NULL;

		if (!list) // if list is empty
		{
			list = tmp;
		}
		else
		{
			last = list;

			// All columns are located in sorted order
			while (last->next)
			{
				if (last->next->col > col)
				{
					tmp->next = last->next;
					last->next = tmp;
					return;
				}
				last = last->next;
			}
			last->next = tmp;
		}
	}

	// Overloaded array subscript operator for const objects
	/*Pre:
	* [in] col - column number to found
	* [var] Element *current is used as iterator to find element
	Post:
	* [out] const double reference for reading operations
	* [modified] nothing
	*/
	const double operator[](const int col) const
	{
		// Check boundaries:
		//if (maxCols < col + 1) assert(0);

		Element* current = list;
		while (current->col != col)
		{
			if (!current->next)
				return 0.0;
			current = current->next;
		}

		return current->value;
	}

	// Overloaded array subscript operator
	/*Pre:
	* [in] col - column number to found
	* [var] Element *current is used as iterator to find element
	Post:
	* [out] double reference for writing operations
	* [modified] added elements to the "list"
	*
	*/
	double& operator[](const int col)
	{
		//if (maxCols < col + 1) assert(0);

		Element* current = list;

		if (!current->next)
		{
			add(col, 0);
			current = current->next;
			return current->value;
		}

		while (current->col != col)
		{
			if (current->next && col > current->col && col < current->next->col)
				add(col, 0.0);
			else if (!current->next)
				add(col, 0.0);

			current = current->next;
		}
		return current->value;
	}

	friend ostream& operator<<(ostream& os, ElementList rhs);
};

/*Pre:
* [in] out - reference to the output stream for printing data
* [in] rhs   - "ElementList" to be printed
* [var] current - is used as iterator in linked list
Post:
* [out] reference to "out" stream
*/
ostream& operator<<(ostream &out, ElementList rhs)
{
	Element* current = rhs.list;
	int ind = 0;
	current = current->next;

	out << "[ ";
	while (current)
	{
		// print zeros for zeros elements
		for (int i = ind; i < current->col; ++i)
			out << "0 ";
		ind = current->col + 1;
		out << current->value << " ";
		current = current->next;
	}

	for (int i = ind; i < rhs.maxCols; ++i)
		out << "0 ";

	out << "] " << endl;
	return out;
}

class SparseMatrix
{

private:
	int numRows;
	int numCols;
	ElementList *rows;

public:
	/*Pre:
	* [in] numC - nubmer of columns in the sparse matrix. Default value is 0, if another is not specified
	* [in] numR - number of rows in the sparse matrix. Default value is 0, if another is not specified
	Post:
	* [out] void
	* [modified] "maxCols", "numRows", "rows"
	*/
	SparseMatrix(int numC = 0, int numR = 0)
	{
		numRows = numC;
		numCols = numR;
		rows = new ElementList[numC];

		for (int i = 0; i < numC; ++i)
			rows[i] = ElementList(numR);
	}

	/*Pre:
	* [in] nothing
	Post:
	* [out] void
	* [modified] "rows" is deleted
	*/
	~SparseMatrix()
	{
		delete[] rows;
	}

	/*Pre:
	* [in] rhs - SparseMatrix to be copied
	Post:
	* [out] void
	* [modified] "maxCols", "numRows", "rows" are initialized by values from rhs
	*/
	SparseMatrix(const SparseMatrix &rhs)
	{
		operator=(rhs);
	}

	// Performs transpose
	/*Pre:
	* [in] nothing
	Post:
	* [out] transposed SparseMatrix
	* [modified] "this" instance is not affected
	*/
	SparseMatrix tr() const
	{
		int numR = this->numRows;
		int numC = this->numCols;

		SparseMatrix out(numC, numR);
		for (int i = 0; i < numR; ++i)
			for (int j = 0; j < numC; ++j)
				out[j][i] = rows[i][j];

		return out;
	}

	/*Pre:
	* [in] rhs - SparseMatrix to be multiplied
	Post:
	* [out] SparseMatrix "out" with result of multiplication
	* [modified] this, rhs is not affected
	*/
	SparseMatrix operator*(const SparseMatrix& rhs) const
	{
		SparseMatrix tr_rhs = rhs.tr();

		int numR = this->numRows;
		int numC = tr_rhs.numCols;
		int numC2 = this->numCols;
		SparseMatrix out(numR, numC);

		for (int i = 0; i < numR; ++i)
			for (int k = 0; k < numC; ++k)
				for (int j = 0; j < numC2; ++j)
				{
					double v1 = this->rows[i][j];
					double v2 = tr_rhs.rows[j][k];
					out[i][k] += v1 * v2;
				}
		return out;
	}

	// Overloaded operator= for deep copy
	/*Pre:
	* [in] rhs - SparseMatrix to be copied
	Post:
	* [out] void
	* [modified] "maxCols", "numRows", "rows" are initialized by values from rhs
	*/
	SparseMatrix& operator=(const SparseMatrix &rhs)
	{
		if (this == &rhs) return *this;

		numRows = rhs.numRows;
		numCols = rhs.numCols;

		rows = new ElementList[numRows];
		for (int i = 0; i < numRows; ++i)
			rows[i] = ElementList(rhs.rows[i]);
		return *this;
	}

	/*Pre:
	* [in] row - row number for access
	Post:
	* [out] ElementList "rows" with index row
	* [modified] "this" instance is not affected
	*/
	const ElementList& operator[](int row) const
	{
		return rows[row];
	}

	/*Pre:
	* [in] row - row number for access
	Post:
	* [out] reference to ElementList "rows" with index row
	*/
	ElementList& operator[](int row)
	{
		return rows[row];
	}

	friend ostream& operator<<(ostream& os, SparseMatrix rhs);
};

/*Pre:
* [in] out - reference to the output stream for printing data
* [in] rhs   - "SparseMatrix" to be printed
Post:
* [out] reference to "out" stream
* [modified] rhs is not affected
*/
ostream& operator<<(ostream& os, SparseMatrix rhs)
{
	for (int i = 0; i < rhs.numRows; ++i)
		os << rhs.rows[i];
	return os;
}

bool elementUnitTst() {

	SparseMatrix sparse(3, 5);
	SparseMatrix square;
	SparseMatrix test(1, 3);

	sparse[0][0] = 1;
	sparse[1][1] = 2;
	sparse[2][2] = 3;
	sparse[2][4] = 4;

	//cout << sparse << endl;

	square = sparse * sparse;
	//cout << "the square of sparse is:\n" << square << endl;

	if (square[0][0] != 1 || square[1][1] != 4 || square[2][2] != 25)
		return false;

	test[0][0] = 3;
	test[0][1] = 6;
	test[0][2] = 9;

	SparseMatrix copy(test);

	//cout << "copy sparse is:" << endl <<copy << endl;

	if (copy[0][0] != 3 || copy[0][1] != 6 || copy[0][2] != 9)
		return false;

	copy = sparse.tr();

	//cout << "transpose of sparse is: " << endl << copy <<endl;

	if (copy[0][0] != 1 || copy[1][1] != 2 || copy[2][2] != 3 || copy[4][2] != 4)
		return false;

	return true;
}

#endif
