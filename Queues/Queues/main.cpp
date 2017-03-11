/* 
This program computes the time it takes for a medical clinic
to do checkups on a village of patients. The total number of
doctors offices available to be visited for the day will be
pre-determined by the user. Each patient is given a time to
arrive and a list of the doctors offices they will be visiting.
The patient will then arrive at his time to the arranged office.
If the office is occupied by another patient, then he/she will
be placed in a queue. After time is increment, the patients
will then move to their next office. If that office is occupied
they will be placed in a queue. After time is incremented, every
patient in a queue will enter the office they are queued for, in
order of first in line, first out of line. When a patient finishes
all of his office visits, he is removed from the patient list.
This cycle will continue until every patient has visited all of
their doctors offices. Once the lists are empty, the loop is broken
and the total incremented time is printed to the screen.

Copyright  Ali Mazeh (c) 2016. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <queue>

// Redefinition of unsigned int to make code shorter.
typedef unsigned int uint;

using namespace std;

/*Pre:
*     [in] totalOffices - must be <= 1000
*     [in] office - will be dynamically allocated queue of max size [totalOffices] (=) <= 1000
*
Post:
*     [out] testEmpty - if the office queue is empty, then return true, else return false.
*/
bool checkEmptyQueue(uint totalOffices, queue<uint> *office)
{
	bool testEmpty = true;

	// Check if all queues of offices are empty
	for (uint i = 0; i < totalOffices; ++i)
	{
		// If queue is not empty return false
		if (!office[i].empty())
			testEmpty = false;
	}

	return testEmpty;
}

/*Pre:
*     [in] numPatients - must be >= 1. Cannot have negative number of patients.
*     [in] list - will be dynamically allocated vector of max size [numPatients] (=) >= 1
*
Post:
*     [out] testEmpty - if the vector list is empty, then return true, else return false.
*/
bool checkEmptyList(uint numPatients, vector<uint> *list)
{
	bool testEmpty = true;

	// Check if all lists of patients are empty
	for (uint i = 0; i < numPatients; ++i)
	{
		// if list is not empty return false
		if (!list[i].empty())
			testEmpty = false;
	}
	return testEmpty;
}

int main()
{
	uint numCases, numPatients, totalOffices, officeVisits, officeNum, localTime;
	bool isEmpty;

	cin >> numCases;

	// Loops per each case
	for (uint iter = 0; iter < numCases; iter++)
	{
		// Read in total number of patients and and total number of dr offices
		cin >> numPatients >> totalOffices;

		// Vector for keeping times when patient should enter to the office
		vector<uint> time(numPatients);

		vector<uint> *list = new vector<uint>[numPatients];
		queue<uint>  *office = new queue<uint>[totalOffices];

		// Loop per each patient to obtain his/her schedule
		for (uint i = 0; i < numPatients; ++i)
		{
			// Time when patient should enter the first office
			cin >> time[i];
			// Read in value for number of offices to visit for that specific patient
			cin >> officeVisits;
			// Allocate memory for patient with number i for k offices to visit
			list[i].resize(officeVisits);
			// Loop for reading list of offices to visit by ith patient
			for (uint j = 0; j < officeVisits; ++j)
				cin >> list[i][j];
		}

		localTime = 0;

		// Run infinite loop for tests with a conditional break
		while (true)
		{
			// isEmpty defines if the loop should break
			isEmpty = true;

			// Call function to check if all queues are empty
			isEmpty = checkEmptyQueue(totalOffices, office);

			// Call function to check if all lists of patients are empty
			isEmpty = checkEmptyList(numPatients, list);

			// If all queues are empty or lists of patients is empty then end loop
			if (isEmpty) break;

			// Loop per each patient
			for (uint i = 0; i < numPatients; i++)
			{
				// Check if patient with number i has non empty list to visit and it's time to enter to the office
				if (time[i] == localTime && !list[i].empty())
				{
					// Get number of office to enter as first number from patient list
					officeNum = list[i][0] - 1;

					// Add patient with number i to the queue
					office[officeNum].push(i);

					// Cross out the first office from list of patients
					list[i].erase(list[i].begin(), list[i].begin() + 1);

					// Update time for patient i, when he/she should enter next office
					time[i] += office[officeNum].size();
				}
			}
			// Increase local time
			localTime++;

			// Loop per offices
			for (uint i = 0; i < totalOffices; i++)
			{
				// If queue is not empty, then we pop first patient from there
				if (!office[i].empty())	office[i].pop();
			}
		}

		// Print time when last patient left the hospital
		cout << localTime << endl;

		// Free allocated memory from queues and vectors
		delete[] office;
		delete[] list;
	}

	return 0;
}
