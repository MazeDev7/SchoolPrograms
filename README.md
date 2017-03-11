# SchoolPrograms
A collection of some of the programs I've written for a class in C++

# Queues

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

# Board Game

This program is a dungeons and dragons style game.
You get a variety of characters: Demon, Dragon, Warrior,
Healer, and cleric. Characters can be either good, evil,
or chaotic. Good and evil can only attack each other while
chaotic can attack everyone. Each character has a
set of attack, health and movement values. Warriors were OP at
one point solo-ing dragons so patch 1.1 nerfed them to 3 max attack.
Dragons can also get a fire breathing ability. After a turn of
moving, an attack is calculated, and if an enemy is within range,
the attack is executed. After attacks are executed, the status of
each character is displayed for you.



# Set Operations

A program built to handle set theory operations implemented with linked lists.
This program allows a user to input multiple set functions
using the keyboard or a file. Up to 10 sets may be active at once.

# Sparse Matrices

This program creates a dynamic array of linked list to hold the
non-zero elements of a matrix. This program provides operations
such as: Addition, subtraction, multiplication, and transposing of
sparse matrices.

# Tournament Tree

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

# Floyd-Warshall Algorithm

This program will generate Dist1, Dist2, Dist3, Path1, Path2, Path3
using the Floyd-Warshall Algorithm.

# Lexical Analyzer

This program mimics a lexical analyzer. It will accept reading in
through text file. It will analyze every string in the code
and determine if it is a keyword, identifier, or number. The program
will self generate these unique tables then generate a token table txt file
based on the program it is reading in.

# Non-rrecursive Parser

This program simulates a compiler based non-recursive predictive parser.

# Copyright  Ali Mazeh (c) 2016. All rights reserved.
