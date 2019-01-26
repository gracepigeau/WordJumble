/*
 * Generate a word search HEADER
 * Created for CISC 320 Assignment 4
 * By Grace Pigeau 10187678
 * Last Edited Nov. 14, 2017
 */

#pragma once

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

typedef char* charArrayPtr;

//Declare the Exception Class which displays a message when an error occurs
class BadJumbleException {
public:
	BadJumbleException(const string&);
	string& what();
private:
	string message;
};

//Decalre the Jumble Puzzle Class
class JumblePuzzle {
public:
	JumblePuzzle(const string, const string); //Default constructor
	JumblePuzzle(const JumblePuzzle&);	//Copy constructor
	~JumblePuzzle();					//Destructor
	charArrayPtr* getJumble() const;	//Accessor
	int getSize() const;				//Accessor
	int getRowPos() const;				//Accessor
	int getColPos() const;				//Accessor
	char getDirection() const;			//Accessor
	JumblePuzzle& operator=(const JumblePuzzle&);	//Overload = operator

private:
	charArrayPtr* jumble;
	int size;
	int rowpos;
	int colpos;
	char direction;
};
