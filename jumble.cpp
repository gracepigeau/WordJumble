#include <iostream>
#include <string>
#include <time.h>

#include "jumble.h"

using namespace std;

typedef char* charArrayPtr;

BadJumbleException::BadJumbleException(const string& m) : message(m) {}
string& BadJumbleException::what() { return message; }

//Default constructor
JumblePuzzle::JumblePuzzle(const string word, const string diff){

	srand(time(0)); //seed random number generator
	const char letters[] = "abcdefghijklmnopqrstuvwxyz"; //create array of alphabet

	int jumblesize(0);
	int wordlen = word.length();

	if (wordlen > 10 || wordlen < 3){
		throw BadJumbleException("Error: Please enter a word with 3-10 letters");
	}
	else if (diff != "easy" && diff != "medium" && diff != "hard"){
		throw BadJumbleException("Error: Please enter a valid difficulty");
	}
	else {
		if (diff == "easy")
			jumblesize = wordlen*2;
		else if (diff == "medium")
			jumblesize = wordlen*3;
		else
			jumblesize = wordlen*4;
		jumble = new char*[jumblesize];
		for (int i = 0; i < jumblesize; i++){
			jumble[i] = new char[jumblesize];
			for (int j = 0; j < jumblesize; j++){
				int tempnum= rand() % 26;
				// Test: cout << "Num at spot: [" << i << "][" << j << "] " << tempnum << endl;
				jumble[i][j] = letters[tempnum];
			}
		}
		int in = 0;
		int row = rand() % jumblesize;
		int col = rand() % jumblesize;

		while (in != 1){
			int dir = rand() % 4; //0=n, 1=e, 2=s, 3=w
			//Test: cout << dir << endl;
			//going up (north)
			if (dir == 0){
				int finish = row-(wordlen-1);
				if (finish >= 0){
					int counter(0);
					for (int ix = row; ix >= finish; ix--){
						jumble[ix][col] = word[counter];
						counter++;
					}
					in = 1;
					direction = 'n';
				}
			}
			//going right (east)
			if (dir == 1){
				int finish = col+(wordlen-1);
				if (finish < jumblesize){
					int counter(0);
					for (int ix = col; ix <= finish; ix++){
						jumble[row][ix] = word[counter];
						counter++;
					}
					in = 1;
					direction = 'e';
				}
			}
			//going down (south)
			if (dir == 2){
				int finish = row+(wordlen-1);
				if (finish < jumblesize){
					int counter(0);
					for (int ix = row; ix <= finish; ix++){
						jumble[ix][col] = word[counter];
						counter++;
					}
					in = 1;
					direction = 's';
				}
			}
			//going left (west)
			if (dir == 3){
				int finish = col-(wordlen-1);
				if (finish >= 0){
					int counter(0);
					for (int ix = col; ix >= finish; ix--){
						jumble[row][ix] = word[counter];
						counter++;
					}
					in = 1;
					direction = 'w';
				}
			}
		}
		rowpos = row;
		colpos = col;
		size = jumblesize;
	}

}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& right){
	size = right.getSize();
	rowpos = right.getRowPos();
	colpos = right.getColPos();
	direction = right.getDirection();

	int jumblesize = right.getSize();
	const charArrayPtr* temp = right.getJumble();

	jumble = new char*[jumblesize];

	for (int i = 0; i < size; i++){
		jumble[i] = new char[jumblesize];
			for (int j = 0; j < size; j++){
				jumble[i][j] = temp[i][j];
			}
		}

}

JumblePuzzle::~JumblePuzzle() {
	for (int i =0; i < size; i++){
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;
}

int JumblePuzzle::getSize() const {
	return size;
}

int JumblePuzzle::getRowPos() const {
	return rowpos;
}

int JumblePuzzle::getColPos() const {
	return colpos;
}

char JumblePuzzle::getDirection() const {
	return direction;
}

charArrayPtr* JumblePuzzle::getJumble() const {

	int jumblesize = size;
	charArrayPtr* togo = new char*[jumblesize];

	for (int i = 0; i < size; i++){
		togo[i] = new char[jumblesize];
		for (int j = 0; j < size; j++){
			togo[i][j] = jumble[i][j];
		}
	}

	return togo;
}

JumblePuzzle& JumblePuzzle::operator =(const JumblePuzzle& right){
	if (this != &right){
		for (int i =0; i < size; i++){
				delete[] jumble[i];
		}
		delete[] jumble;
		size = right.getSize();

		int jumblesize = right.getSize();
		const charArrayPtr* temp = right.getJumble();

		jumble = new char*[jumblesize];

		for (int i = 0; i < size; i++){
			jumble[i] = new char[jumblesize];
			for (int j = 0; j < size; j++){
				jumble[i][j] = temp[i][j];
			}
		}
	}
	return *this;
}
