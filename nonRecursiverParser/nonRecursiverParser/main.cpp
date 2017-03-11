/*
This program simulates a non-recursive predictive parser.


Created by Ali Mazeh on 10/10/16.
Copyright © 2016 Ali Mazeh. All rights reserved.
*/

#include <iostream>
#include <stack>
#include <iomanip>
#include <deque>
#include <string>
#include <fstream>

using namespace std;

void printInfo(deque<char> &parseStack, deque<char> &input, deque<char> &matched) {
	char temp;
	string s_input, s_stack;
	int it;
	deque<char> output;
	ofstream outs;
	outs.open("output.txt", ios::app);

	for (it = 0; it< matched.size(); it++) {
		outs << matched[it];
	}
	outs << setw(10 - it) << "|";

	for (int i = (int)parseStack.size() - 1; i >= 0; i--) {
		temp = parseStack[i];

		if (temp == 'e') {
			s_stack.push_back('E');
			s_stack.push_back(39);
		}
		else if (temp == 't') {
			s_stack.push_back('T');
			s_stack.push_back(39);
		}
		else
			s_stack.push_back(temp);
	}

	outs << setw(15) << right << s_stack << setw(3) << "|";

	for (int i = 0; i < input.size(); i++)
		s_input.push_back(input[i]);

	outs << setw(15) << right << s_input << setw(3) << "|" << endl;
}

void findIndex(string parseTable[6][7], int *firstIndex, int *secondIndex, char stackChr, char inputCh) {

	for (int i = 0; i < 6; i++)
		if (stackChr == parseTable[i][0][0])
			*firstIndex = i;

	for (int i = 0; i < 7; i++)
		if (inputCh == parseTable[0][i][0])
			*secondIndex = i;
}

int main() {

	int *p, *q, f_index = 0, s_index = 0;
	deque<char> input, parseStack, matched;
	char test[8] = { '(', 'i','+','i', ')', '*', 'i', '$' };
	string parseTable[6][7] = { "0", "i", "+", "*", "(",")","$",
		"E", "Te","0", "0", "Te", "0", "0",
		"e", "0", "+Te","0", "0", "3", "3",
		"T", "Ft", "0", "0", "Ft", "0", "0",
		"t", "0", "3", "*Ft", "0", "3", "3",
		"F",  "i", "0", "0", "(E)", "0", "0" };
	ofstream outs;
	outs.open("output.txt");

	for (int i = 0; i<8; i++)
		input.push_back(test[i]);

	parseStack.push_back('$');
	parseStack.push_back('E');

	outs << setw(3) << "Matched" << setw(16) << "Stack" << setw(17) << "Input" << endl;
	outs << "______________________________________________" << endl;

	p = &f_index;
	q = &s_index;

	printInfo(parseStack, input, matched);

	while (parseStack.back() != '$') {
		findIndex(parseTable, p, q, parseStack.back(), input[0]);

		if (parseStack.back() == input[0]) {
			matched.push_back(input.front());
			parseStack.pop_back();
			input.pop_front();

			printInfo(parseStack, input, matched);
		}
		else if (parseTable[f_index][s_index] == "0") cout << "Error";
		else {
			parseStack.pop_back();

			if (parseTable[f_index][s_index] != "3") {
				for (int i = (int)parseTable[f_index][s_index].size() - 1; i >= 0; i--)
					parseStack.push_back(parseTable[f_index][s_index][i]);
			}
			printInfo(parseStack, input, matched);
		}
	}
	return 0;
}
