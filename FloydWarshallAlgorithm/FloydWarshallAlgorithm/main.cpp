/*
This program will generate Dist1, Dist2, Dist3, Path1, Path2, Path3
using the Floyd-Warshall Algorithm.

Created by Ali Mazeh on 11/28/16.
Copyright © 2016 Ali Mazeh. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

const int MATRIXSIZE = 4;

void printTables(vector<vector<int>> &dist, vector<vector<int>> &path, int it)
{
	string table1 = "";
	string table2 = "";

	if (it == -1) {
		it++;
		table1 = "Og D";
		table2 = "Og P";
	}
	else {
		table1 = "d";
		table2 = "p";
	}

	cout << table1 << it << ':' << setw(12) << table2 << it << ":" << endl;

	for (int i = 0; i < MATRIXSIZE; i++) {
		string t1 = "";
		string t2 = "";

		for (int j = 0; j < MATRIXSIZE; j++) {
			if (dist[i][j] != 999 && path[i][j] != 999) {
				if (dist[i][j] >= 0)
					t1 += " " + to_string(dist[i][j]) + " ";
				else
					t1 += to_string(dist[i][j]) + " ";
				t2 += to_string(path[i][j]) + " ";
			}
			else if (dist[i][j] == 999 && path[i][j] != 999) {
				t1 += " ";
				t1.append(1, '-');
				t1 += " ";
				t2 += to_string(path[i][j]) + " ";
			}
			else if (dist[i][j] != 999 && path[i][j] == 999) {
				if (dist[i][j] >= 0)
					t1 += " " + to_string(dist[i][j]) + " ";
				else
					t1 += to_string(dist[i][j]) + " ";
				t2 += "- ";
			}
			else
			{
				t1 += " ";
				t1.append(1, '-');
				t1 += " ";
				t2 += "- ";
			}
		}

		if (t1.compare(t2) > 0)
			cout << " " << (t1 += (" " + t2)) << endl;
		else
			cout << (t1 += ("  " + t2)) << endl;
	}
	cout << endl;
}

void floydAlgo(vector<vector<int>> &dist, vector<vector<int>> &path)
{
	printTables(dist, path, 0);

	for (int k = 1; k < MATRIXSIZE; k++) {
		for (int i = 0; i < MATRIXSIZE; i++) {
			if (i == k)
				dist[i][k] = 0;

			for (int j = 0; j < MATRIXSIZE; j++) {
				if (dist[i][k] == 999 || dist[k][j] == 999)
					continue;
				if (dist[i][j] >(dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
		printTables(dist, path, k);
	}
}

int main()
{
	vector<vector<int>> D = { { 0, 999, 3, 0 },{ -2, 0, 999, 1 },{ 999, 999, 0, 5 },{ 999, 4, 999, 0 } };
	vector<vector<int>> P = { { 999, 999, 0, 0 },{ 1, 999, 999, 1 },{ 999, 999, 999, 2 },{ 999, 3, 999, 999 } };

	floydAlgo(D, P);

	return 0;
}
