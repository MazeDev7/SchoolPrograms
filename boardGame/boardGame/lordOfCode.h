/*
Ali H. Mazeh

lordOfTheCode.hpp
program 3

This program is a dungeons and dragons style game.
You get a variety of characters: Demon, Dragon, Warrior,
Healer, and cleric. Characters can be either good, evil,
or chaotic. Good and evil can only attack each other while
chaotic can attack everyone(oooo scary). Each character has a
set of attack, health and movement values. Warriors were OP at
one point solo-ing dragons so patch 1.1 nerfed them to 3 max attack.
Dragons can also get a fire breathing ability. After a turn of
moving, an attack is calculated, and if an enemy is within range,
the attack is executed. After attacks are executed, the status of
each character is displayed for you.

Created by Ali Mazeh on 3/18/16.
Copyright (c) 2016 Ali Mazeh. All rights reserved.
*/


#ifndef lordOfTheCode_hpp
#define lordOfTheCode_hpp

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <typeinfo>

using namespace std;

// Represents set of constants
enum type
{
	good,   // corresponds to default value 0
	evil,   // corresponds to default value 1
	chaotic // corresponds to default value 2
};

class Character
{
public:

	bool cursed, blessed;
	string name;
	// Type of character: good, evil, chaotic
	type alignment;
	unsigned int attackStr, healthStr, maxHealth, maxAttack, range;
	int xLoc, yLoc;

public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	Character(int x, int y, string goodBadUgly, string charName)
	{
		xLoc = x;
		yLoc = y;

		if (goodBadUgly == "good")
			alignment = good;
		else if (goodBadUgly == "evil")
			alignment = evil;
		else if (goodBadUgly == "chaotic")
			alignment = chaotic;

		name = charName;
	}

	/*Pre:
	* [in] who - character passed by reference to attack
	Post:
	* [out] void
	* [modified] healthStr of who can be updated
	*/
	// Warrior, Cleric
	virtual void attack(Character& who)
	{
		// Avoid attacking self
		if (this == &who) return;

		// Check if attacking character and attacked character belong to different alignments
		if (alignment != who.alignment && who.alignment != chaotic)
		{
			// Calculate distance between 2 characters and round it using ceil
			unsigned int dist = (unsigned int)ceil(hypot(who.xLoc - xLoc, who.yLoc - yLoc));

			// If range is good for an attack, then attack
			if (range >= dist)
			{
				// Decrease health strength by value of out attackStr
				if ((int)(who.healthStr - attackStr) < 0) who.healthStr = 0;
				else who.healthStr -= attackStr;
			}
		}
	}

	/*Pre:
	* [in] void
	Post:
	* [out] void
	* [modified] xLoc, yLoc are updated
	*/
	void move()
	{
		// If character is dead(0 health) then it can't move
		if (healthStr == 0) return;

		if (strstr(typeid(*this).name(), "Demon") != NULL)
			moveDirect(1, 2); // If a Demon, move in (1,2) direction
		else if (strstr(typeid(*this).name(), "Dragon") != NULL)
			moveDirect(-1, -1); // If a Dragon, move in (-1,-1) direction
		else if (strstr(typeid(*this).name(), "Healer") != NULL)
		{
			moveDirect(1, 1); // If a Healer, move in (1,1) direction
			if (cursed && healthStr > 0) healthStr--; // If cursed, then healthStr is descreased
			if (blessed && healthStr < maxHealth) healthStr++; // If blessed, then healthStr is increased
		}
		else if (strstr(typeid(*this).name(), "Cleric") != NULL)
		{
			moveDirect(1, 1); // If a Cleric, move in (1,1) direction
			if (cursed && healthStr > 0) healthStr--; // If cursed, then healthStr is descreased
			if (blessed && healthStr < maxHealth) healthStr++; // If blessed, then healthStr is increased
		}
		else if (strstr(typeid(*this).name(), "Warrior") != NULL)
		{
			moveDirect(1, 1); // If a Warrior, move in (1,1) direction
			if (cursed && healthStr > 0) healthStr--; // If cursed, than healthStr is descreased
			if (blessed && healthStr < maxHealth) healthStr++; // If blessed, than healthStr is increased
		}
	}

	/*Pre:
	* [in] xDir - move in this direction along x-axis
	* [in] yDir - move in this direction along y-axis
	Post:
	* [out] void
	* [modified] xLoc, yLoc are updated
	*/
	void moveDirect(int xDir, int yDir)
	{
		xLoc += xDir;
		yLoc += yDir;
	}

	/*Pre:
	* [in] void
	Post:
	* [out] string
	* [modified] nothing
	*/
	// This function does nothing and is never executed
	// It's a virtual function and is redefined in classes below
	virtual string status()
	{
		return "";
	}

};

class Dragon : public Character
{
public:
	// true - fire breathing, false - no fire :(
	bool fireBreathing;

public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	* [in] fire - yes, no
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name, fireBreathing are updated
	*/
	// constructor
	Dragon(int x, int y, string goodBadUgly, string charName, char fire) : Character(x, y, goodBadUgly, charName)
	{
		range = 10;
		maxHealth = 10;

		// maxAttack depends on fire parameter
		if (fire == 'f')
		{
			fireBreathing = true;
			maxAttack = 10;
		}
		else if (fire == 'b')
		{
			fireBreathing = false;
			maxAttack = 5;
		}

		healthStr = maxHealth;
		attackStr = maxAttack;
	}

	/*Pre:
	* [in] nothing
	Post:
	* [out] string
	* [modified] nothing
	*/
	// This function is called instead of Character's status
	string status()
	{
		// Variables for converted values from integers to strings
		string health, attack, x, y, fire;
		// String stream for conversion
		ostringstream convert;

		// Convert healthStr by putting its integer value to the stream
		convert << healthStr;
		// And getting it back in string format
		health = convert.str();

		// Flush stream
		convert.str("");
		convert.clear();
		convert << attackStr;
		attack = convert.str();

		// Flush stream
		convert.str("");
		convert.clear();
		convert << xLoc;
		x = convert.str();

		// Flush stream
		convert.str("");
		convert.clear();
		convert << yLoc;
		y = convert.str();

		// Convert boolean value manually
		fire = (fireBreathing == true) ? "true" : "false";

		// Return output string in specified format
		return "name    : " + name + "\ntype    : " + typeid(*this).name() + "\nhealth  : "
			+ health + "\nattack  : " + attack + "\nlocation: (" + x + ", " + y + ")\nfire    : " + fire + "\n";
	}
};

class Demon : public Character
{
public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	// constructor
	Demon(int x, int y, string goodBadUgly, string charName) : Character(x, y, goodBadUgly, charName)
	{
		range = 1;
		maxHealth = 5;
		maxAttack = 3;

		healthStr = maxHealth;
		attackStr = maxAttack;
	}

	/*Pre:
	* [in] who - character passed by reference to attack
	Post:
	* [out] void
	* [modified] healthStr of who can be updated
	*/
	void attack(Character& who)
	{
		// Prevent attacking self
		if (this == &who) return;

		// Calculate distance
		unsigned int dist = (unsigned int)ceil(hypot(who.xLoc - xLoc, who.yLoc - yLoc));
		// If who belongs to Humanoid then attack
		if (range >= dist && (strstr(typeid(who).name(), "Warrior") != NULL || strstr(typeid(who).name(), "Healer") != NULL || strstr(typeid(who).name(), "Cleric") != NULL))
		{
			if (who.blessed == true) who.blessed = false; // Cancel out blessed parameter if they're already blessed
			else who.cursed = true; // and curse if not blessed
		}
	}

	/*Pre:
	* [in] nothing
	Post:
	* [out] string
	* [modified] nothing
	*/
	// This function is called instead of Character's status
	string status()
	{
		// Variables for converted values from integers to strings.
		string health, attack, x, y;
		// String stream for conversion
		ostringstream convert;

		// Convert healthStr to string data type
		convert << healthStr;
		health = convert.str();

		// Flush stream
		convert.str("");
		convert.clear();
		convert << attackStr;
		attack = convert.str();

		convert.str("");
		convert.clear();
		convert << xLoc;
		x = convert.str();

		convert.str("");
		convert.clear();
		convert << yLoc;
		y = convert.str();

		// Return output string in specified format
		return "name    : " + name + "\ntype    : " + typeid(*this).name() + "\nhealth  : "
			+ health + "\nattack  : " + attack + "\nlocation: (" + x + ", " + y + ")\n";
	}

};

class Humanoid : public Character
{
public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	// Constructor
	Humanoid(int x, int y, string goodBadUgly, string charName) : Character(x, y, goodBadUgly, charName)
	{
		cursed = false;
		blessed = false;
	}

	/*Pre:
	* [in] nothing
	Post:
	* [out] string
	* [modified] nothing
	*/
	// This function is called instead of Character's status
	string status()
	{
		// Variables for converted values from integers to strings
		string health, attack, x, y, isCursed, isBlessed, classType;
		// String stream for conversion
		ostringstream convert;

		// Convert healthStr to string data type
		convert << healthStr;
		health = convert.str();

		// Flush stream
		convert.str("");
		convert.clear();
		convert << attackStr;
		attack = convert.str();

		convert.str("");
		convert.clear();
		convert << xLoc;
		x = convert.str();

		convert.str("");
		convert.clear();
		convert << yLoc;
		y = convert.str();

		// Convert cursed manually
		if (cursed) isCursed = "true";
		else isCursed = "false";

		// Convert blessed manually
		if (blessed) isBlessed = "true";
		else isBlessed = "false";

		// Return output string in specified format
		return "name    : " + name + "\ntype    : " + typeid(*this).name() + "\nhealth  : "
			+ health + "\nattack  : " + attack + "\nlocation: (" + x + ", " + y + ")\n" +
			"cursed  : " + isCursed + "\nblessed : " + isBlessed + "\n";
	}

};


class Healer : public Humanoid
{
public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	// Constructor
	Healer(int x, int y, string goodBadUgly, string charName) : Humanoid(x, y, goodBadUgly, charName)
	{
		range = 1;
		maxHealth = 2;
		maxAttack = 0;

		healthStr = maxHealth;
		attackStr = maxAttack;
	}

	/*Pre:
	* [in] who - character passed by reference to attack
	Post:
	* [out] void
	* [modified] healthStr of who can be updated
	*/
	void attack(Character& who)
	{
		// Avoid attacking self
		if (this == &who) return;


		if (alignment == who.alignment)
		{
			// Check distance between characters
			unsigned int dist = (unsigned int)ceil(hypot(who.xLoc - xLoc, who.yLoc - yLoc));
			// If distance is good, then increase healthStr of who to its max
			if (range >= dist)
				who.healthStr = who.maxHealth;
		}
	}

};

class Cleric : public Humanoid
{
public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	// Constructor
	Cleric(int x, int y, string goodBadUgly, string charName) : Humanoid(x, y, goodBadUgly, charName)
	{
		range = 1;
		maxHealth = 2;
		maxAttack = 0;

		healthStr = maxHealth;
		attackStr = maxAttack;
	}

	/*Pre:
	* [in] who - character passed by reference to attack
	Post:
	* [out] void
	* [modified] healthStr of who can be updated
	*/
	void attack(Character& who)
	{
		// Avoid attacking self
		if (this == &who) return;

		// Check if who and this belong to the same ally
		if (alignment == who.alignment)
		{
			// Calculate distance between them
			unsigned int dist = (unsigned int)ceil(hypot(who.xLoc - xLoc, who.yLoc - yLoc));

			// Check distance and data type of who - can attack only Humanoids
			if (range >= dist && (strstr(typeid(who).name(), "Warrior") != NULL || strstr(typeid(who).name(), "Healer") != NULL || strstr(typeid(who).name(), "Cleric") != NULL))
			{
				// who is passed as a Character, but I need to access the cursed, blessed fields.
				// That's why I moved them from Humanoid class to Chracter class, only way I could get it to work.
				if (who.cursed == true) who.cursed = false; // Cancel out curse
				else who.blessed = true; // Bless if not cursed
			}
		}
	}
};

class Warrior : public Humanoid
{
public:

	/*Pre:
	* [in] x - character position on x-axis
	* [in] y - character position on y-axis
	* [in] goodBadUgly - character alignment (evil, good, chaotic)
	* [in] charName - character name
	Post:
	* [out] void
	* [modified] xLoc, yLoc, alignment, name are updated
	*/
	// Constructor
	Warrior(int x, int y, string goodBadUgly, string charName) : Humanoid(x, y, goodBadUgly, charName)
	{
		range = 1;
		maxHealth = 5;
		maxAttack = 3;

		healthStr = maxHealth;
		attackStr = maxAttack;
	}

};

#endif
