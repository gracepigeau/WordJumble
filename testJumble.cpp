/*
 * A testing class for your JumblePuzzle class and its exception. 
 * The code also contains a simple function written by Professor McLeod that allows you to play the game, and
 * another function that you can use to display the puzzle.
 */
#include <string>
#include <iostream>
#include <ctime>
#include "jumble.h"
using namespace std;

// Displays the puzzle to the screen.
// Row and column numbers are added to the display.
void showJumble(const charArrayPtr* jumble, const int size) {
	int i, j;
	cout << "\n  ";
	for (i = 0; i < size; i++)
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
	cout << endl;
	for (i = 0; i < size; i++) {
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
		for (j = 0; j < size; j++)
			cout << jumble[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
} // end showJumble

// How quickly can you find the hidden string?
void playGame() {
	string toHide;
	string difficulty;
	int guessRow, guessCol;
	int start, finish;
	char guessDirection;

	cout << "Provide a string to hide in the puzzle, all lower case: ";
	cin >> toHide;
	cout << "\nChoose your difficulty level: \"easy\", \"medium\" or \"hard\": ";
	cin >> difficulty;

	JumblePuzzle* jp;
	try {
		jp = new JumblePuzzle(toHide, difficulty);
	} catch (BadJumbleException& e) {
		cerr << e.what();
		return;
	}
	showJumble(jp->getJumble(), jp->getSize());
	start = static_cast<int>(time(nullptr));
	cout << "Enter row location: ";
	cin >> guessRow;
	cout << "Enter column location: ";
	cin >> guessCol;
	cout << "Enter direction (\"n\", \"e\", \"s\" or \"w\"): ";
	cin >> guessDirection;
	finish = static_cast<int>(time(nullptr));
	if (guessRow == jp->getRowPos() && guessCol == jp->getColPos() &&
			guessDirection == jp->getDirection())
		cout << "You found it!" << endl;
	else {
		cout << "Wrong location..." << endl;
		cout << "The location is row: " << jp->getRowPos() << " col: " << jp->getColPos()
				<< ", direction: " << jp->getDirection() << endl;
	}
	cout << "You took " << (finish - start) << " seconds." << endl;
	delete jp;
	jp = nullptr;
} // end playGame

// Unit tests are provided to test your copy constructor, your assignment overloading and aliasing,
// that exceptions are thrown when they should be, that the puzzle is the correct size and is formed properly, and
// that the accessors return what they should.
void testJumble() {

	// Test copy constructor for proper operation
	cout << "Testing copy constructor:" << endl;
	// While debugging, you can use capital letters to make the hidden string easier to locate
	JumblePuzzle jp1("HELLO", "easy");
	showJumble(jp1.getJumble(), jp1.getSize());
	JumblePuzzle jp2(jp1);
	cout << "Should look the same:" << endl;
	showJumble(jp2.getJumble(), jp2.getSize());

	// Test aliasing from copy constructor
	charArrayPtr* puzzle = jp2.getJumble();
	int sz = jp2.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '.';
	cout << "Dotted diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 1:" << endl;
	showJumble(jp1.getJumble(), sz);
	cout << "Should be same as original 2:" << endl;
	showJumble(jp2.getJumble(), sz);

	// Test assignment operator for proper operation
	cout << "Testing assignment operator:" << endl;
	JumblePuzzle jp3("BYE", "easy");
	showJumble(jp3.getJumble(), jp3.getSize());
	JumblePuzzle jp4 = jp3;
	cout << "Should look the same:" << endl;
	showJumble(jp4.getJumble(), jp4.getSize());

	// Test aliasing from assignment operator
	puzzle = jp4.getJumble();
	sz = jp4.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '*';
	cout << "Star diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 3:" << endl;
	showJumble(jp3.getJumble(), sz);
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test self-assignment
	// This shows as a "bug", which it should do.  However, you should still
	// be able to build and run program.
	jp4 = jp4;
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test for a memory leak.
	// This is a pretty slow test and it may be that the limit of the loop
	// will not be large enough to show a memory leak, especially if you have
	// quite a bit of RAM.
	int loopLimit = 1000;
	for (int i = 0; i < loopLimit; i++)
		JumblePuzzle jp("HIDDENWORD", "hard");
	cout << "\nPassed memory leak test!" << endl;

	//Test for proper error handling of wrong length word
	cout << "Testing with too long of a word:" << endl;
	try {
		JumblePuzzle jpbad1("HELLOTHERESIR", "easy");
	}
	catch (BadJumbleException& e) {
		cout << e.what() << endl;
	}
	cout << "Testing with too short of a word:" << endl;
	try {
		JumblePuzzle jpbad2("HE", "easy");
	}
	catch (BadJumbleException& e) {
		cout << e.what() << endl;;
	}

	//Test for proper error handling of invalid difficulty input
	cout << "Testing with an invalid difficulty input:" << endl;
	try {
		JumblePuzzle jpbad3("HELLO", "easyr");
	}
	catch (BadJumbleException& e) {
		cout << e.what() << endl;
	}

} // end testJumble

int main() {

	testJumble();
	playGame();

	return 0;
} // end main
