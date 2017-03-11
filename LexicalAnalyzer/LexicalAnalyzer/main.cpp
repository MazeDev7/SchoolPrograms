/*
This program mimics a lexical analyzer. It will accept reading in
through text file. It will analyze every string in the code
and determine if it is a keyword, identifier, or number. The program
will self generate these unique tables then generate a token table
based on the program it is reading in.


Created by Ali Mazeh on 9/24/16.
Copyright © 2016 Ali Mazeh. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

ifstream ins;
ofstream outs;

void printProgram(vector<string> file) {
	int i = 1;
	string input;

	file.clear();

	ins.open("input.txt");
	outs.open("tokenTable.txt");

	while (getline(ins, input)) {
		if (input[0] != '/' && input[1] != '*') {
			file.resize(i);
			file.push_back(input);
			i++;
		}
	}

	outs << "Program with comments stripped" << endl << "________________________________" << endl;

	for (int i = 0; i < file.size(); i++)
		outs << file[i] << endl;
}

void printTables(string keywords[25][2], vector<vector<string>> &numTable, vector<vector<string>> &idTable, vector<vector<string>> &tokenTable) {

	outs << setw(5) << "\nKeyword" << setw(8) << "Index" << endl;
	outs << "________________" << endl;

	for (int i = 0; i < 25; i++) {
		outs << endl;
		for (int j = 0; j < 2; j++)
			outs << setw(10) << left << keywords[i][j] << " ";
	}

	outs << setw(11) << "\n\n\nId" << setw(8) << "Index" << endl;
	outs << "________________" << endl;

	for (int i = 0; i < idTable.size(); i++)
		outs << setw(10) << left << idTable[i][0] << setw(10) << left << idTable[i][1] << endl;


	outs << setw(11) << "\n\nNumber" << setw(8) << "Index" << endl;
	outs << "________________" << endl;

	for (int i = 0; i < numTable.size(); i++)
		outs << setw(10) << left << numTable[i][0] << setw(10) << left << numTable[i][1] << endl;

	outs << setw(12) << "\n\nToken" << setw(11) << "Class" << setw(10) << "Index" << endl;
	outs << "___________________________" << endl;

	for (int i = 0; i < tokenTable.size(); i++)
		outs << setw(10) << left << tokenTable[i][0] << setw(12) << left << tokenTable[i][1] << setw(14) << left << tokenTable[i][2] << endl;
}

bool isNumber(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool isDuplicate(string s, vector<vector<string>> &numTable, vector<vector<string>> &idTable, string keywords[25][2]) {
	bool duplicate = false;

	for (int i = 0; i < numTable.size(); i++)
		if (s == numTable[i][0]) duplicate = true;

	for (int i = 0; i < idTable.size(); i++)
		if (s == idTable[i][0]) duplicate = true;

	for (int i = 0; i < 25; i++)
		if (s == keywords[i][0]) duplicate = true;

	return duplicate;
}

bool idCheck(string s, vector<vector<string>> &idTable, string keywords[15][2]) {
	bool numTest = false, result = false, keyTest = false;

	numTest = isNumber(s);

	for (int i = 0; i < 25; i++)
		if (s == keywords[i][0]) keyTest = true;

	if (numTest == false && keyTest == false)
		result = true;

	return result;
}

bool keywordCheck(string s, string keywords[25][2], string *p) {
	bool isKey = false;

	for (int i = 0; i < 25; i++)
		if (s == keywords[i][0]) {
			isKey = true;
			*p = keywords[i][1];
		}
	return isKey;
}

int main() {
	string keywords[25][2] = { "int", "1", "if", "2" ,"return", "3", "else", "4", "void", "5",
		"while", "6", "(", "7", ")", "8", "{", "9", "}", "10", "*", "11", "=", "12", ">", "13", "-", "14", ";","15",
		"+", "16", "/", "17", "<", "18", "<=", "19", ">=", "20", "==", "21", "!=", "22", ",", "23", "/*", "24", "*/", "25" };
	string word, number, classType, index, keyIndex = "0", *p;
	vector<string> fileInput;
	bool isDigit = false, isId = false, duplicate = false, isComment = false, isKeyword = false;
	vector<vector<string>> numTable, idTable, tokenTable;
	int numSize = 1, idSize = 1, tokenSize = 1;

	ifstream ins;
	ofstream outs;

	ins.open("input.txt");


	if (ins) {
		while (!ins.eof()) {

			ins >> word;

			if (word == "/*") isComment = true;

			if (isComment == false) fileInput.push_back(word);

			if (word == "*/") isComment = false;
		}
	}
	else
		outs << "File not opened";

	p = &keyIndex;

	for (int i = 0; i < fileInput.size(); i++) {

		duplicate = isDuplicate(fileInput[i], numTable, idTable, keywords);
		isDigit = isNumber(fileInput[i]);
		isKeyword = keywordCheck(fileInput[i], keywords, p);
		isId = idCheck(fileInput[i], idTable, keywords);

		if ((duplicate == false) && (isDigit == true)) {
			numTable.resize(numSize);
			numTable[numSize - 1].push_back(fileInput[i]);
			number = to_string(numSize);
			numTable[numSize - 1].push_back(number);

			numSize++;
		}

		if ((duplicate == false) && (isId == true)) {
			idTable.resize(idSize);
			idTable[idSize - 1].push_back(fileInput[i]);
			number = to_string(idSize);
			idTable[idSize - 1].push_back(number);

			idSize++;
		}

		duplicate = false;
		isKeyword = false;
		isId = false;
		isDigit = false;
	}

	for (int i = 0; i < fileInput.size(); i++) {

		for (int j = 0; j < idTable.size(); j++) {
			if (fileInput[i] == idTable[j][0]) {
				isId = true;
				index = idTable[j][1];
			}
		}
		for (int j = 0; j < numTable.size(); j++) {
			if (fileInput[i] == numTable[j][0]) {
				isDigit = true;
				index = numTable[j][1];
			}
		}

		isKeyword = keywordCheck(fileInput[i], keywords, p);

		if (isDigit == true || isId == true || isKeyword == true) {
			tokenTable.resize(tokenSize);
			tokenTable[tokenSize - 1].push_back(fileInput[i]);

			if (isDigit == true) classType = "number";
			if (isKeyword == true) classType = "keyword";
			if (isId == true) classType = "id";

			tokenTable[tokenSize - 1].push_back(classType);

			if (isKeyword == true)
				tokenTable[tokenSize - 1].push_back(keyIndex);
			else
				tokenTable[tokenSize - 1].push_back(index);

			tokenSize++;
		}

		isKeyword = false;
		isId = false;
		isDigit = false;
	}

	printProgram(fileInput);
	printTables(keywords, numTable, idTable, tokenTable);

	ins.close();
	outs.close();

	return 0;
}
