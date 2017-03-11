#include <iostream>
#include "lordOfCode.h"

using namespace std;



int main() {
	Character ** characters; // all characters will start at maxHealth and maxAttack
	int numChar; 
	//cout<<"How many characters do you want ?"; 
	//cin>> numChar;
	numChar = 6;
	characters = new Character *[numChar];
	characters[0] = new Demon(0, 0, "chaotic", "Etrigan");
	characters[1] = new Dragon(20, 20, "evil", "Eragon", 'f');// f for fire Breathing,
	characters[2] = new Dragon(10, 10, "evil", "Glaurung", 'b');// b for Bite,
	characters[3] = new Warrior(0, 0, "good", "Xena");
	characters[4] = new Healer(0, 0, "good", "Bones");
	characters[5] = new Cleric(0, 0, "good", "Shaolin");
	cout << "inital status:\n";
	for (int i = 0; i < numChar; i++) cout << characters[i]->status() << endl;
	for (int i = 0; i < numChar; i++) characters[i]->move();
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
	cout << "after movement:\n";
	for (int i = 0; i < numChar; i++) cout << characters[i]->status() << endl;
	for (int i = 0; i < numChar; i++)
		for (int j = 0; j< numChar; j++)
			if (i != j) characters[i]->attack(*characters[j]);
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
	cout << "after attack:\n";
	for (int i = 0; i < numChar; i++) cout << characters[i]->status() << endl;
	return 0;
}