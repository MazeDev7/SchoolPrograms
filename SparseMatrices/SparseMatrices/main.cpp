//
//  main.cpp
//  SparseMatrices
//
//  Created by Ali Mazeh on 2/5/16.
//  Copyright (c) 2016 Ali Mazeh. All rights reserved.
//

#include "sparse_mtrx.h"

int main()
{
	SparseMatrix sparse(3, 5);
	SparseMatrix square;

	sparse[0][0] = 1;
	sparse[1][1] = 2;
	sparse[2][2] = 3;
	sparse[2][4] = 4;

	cout << sparse << endl;
	cout << sparse[2][3] << endl;

	square = sparse * sparse;
	cout << "the square of sparse is:\n" << square << endl;
	cout << sparse << endl;

	const SparseMatrix c_mtrx(sparse);
	cout << "Copy of sparse:\n" << c_mtrx << endl;
	double test = c_mtrx[0][4];
	cout << "sparse[0][4]: " << test << endl;

	SparseMatrix copy;
	copy = sparse.tr();
	cout << "Transpose of sparse:\n" << copy << endl;
	cout << "Sparse:\n" << sparse << endl;

	ElementList lst1(5);
	lst1.add(1, 1);
	lst1.add(4, 10);
	lst1.add(2, 3);
	cout << "lst1: " << lst1 << endl;

	ElementList lst2(5);
	lst2.add(0, 20);
	lst2.add(4, -50);
	lst2.add(2, 2);
	cout << "lst2: " << lst2 << endl;

	lst1 = lst1 + lst2;
	cout << "lst1 + lst2: " << lst1 << endl;
	cout << "lst2: " << lst2 << endl;

	return 0;
}