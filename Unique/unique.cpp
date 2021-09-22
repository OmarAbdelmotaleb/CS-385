/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Omar Abdelmotaleb
 * Date        : 09/25/20
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/**
 * Checks if all characters in string s is lowercase
 */
bool is_all_lowercase(const string &s) {

	for(int const &c: s) {
		// 97 = 'a' and 122 = 'z',
		// checks to see if c is within the range of a-z
		if(c < 97 || c > 122) {
			return false;
		}
	}
	return true;

}

/**
 * Checks if all characters in string s is unique
 */
bool all_unique_letters(const string &s) {

	// Vector
	unsigned int vect = 0;

	// Iterates through every character in string
	for(int const &c: s) {

		// 1 << c - 'a' is the setter
		if( ( vect & (1 << (c - 'a')) ) != 0 ) {
			return false;
		}

		vect = vect | (1 << (c - 'a'));
	}

	return true;

}

int main(int argc, char * const argv[]) {

	string unique_string;

	// Checks if args are only ./unique and a string
	if(argc != 2) {
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}

	unique_string = argv[1];

	// If string is not lowercase, then output an error
	if( !(is_all_lowercase(unique_string)) ) {
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	// Outputs if all letter are unique or not
	if(all_unique_letters(unique_string)) {
		cout << "All letters are unique." << endl;
		return 0;
	}
	else {
		cout << "Duplicate letters found." << endl;
		return 0;
	}

	return 0;

}
