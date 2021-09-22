/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Omar Abdelmotaleb and Benjamin Singleton
 * Version : 1.0
 * Date    : December 7, 2020
 * Description : Solve the all pairs shortest paths problem with Floyd’s algorithm.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <iomanip>
#include <climits>
#include <vector>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <valarray>
#include <regex>

using namespace std;

long INF = LONG_MAX;
int num_vertices;
vector<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
long** intermediates;
long** lengths;


int len(long num) {
	if (num == 0) {
		return 1;
	}
	int count = 0;
	while (num >= 1) {
		num = num/10;
		count = count + 1;
	}
    return count;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = use_letters ? len(max_val) :
			len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

long** make_distance_matrix() {
	long** matrix = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		matrix[i] = new long[num_vertices];
	}

	for (int i = 0; i < num_vertices; i++ ) {
		for (int j = 0; j < num_vertices; j++) {
			matrix[i][j] = INF;
		}
	}

	return matrix;
}

long** make_matrices(long** const lengths) {
	for (int k = 0; k < num_vertices; k++) {
		for (int i = 0; i < num_vertices; i++) {
			for (int j = 0; j < num_vertices; j++) {
				if (lengths[i][k] != INF && lengths[k][j] != INF) {
					if (lengths[i][j] > lengths[i][k] + lengths[k][j]) {
						lengths[i][j] = lengths[i][k] + lengths[k][j];
						intermediates[i][j] = k;
					}
				}
			}
		}
	}
	return lengths;
}

vector<char> helper(int i, int j) {
	if (intermediates[i][j] == INF) {
		vector<char> answer;
		answer.push_back(static_cast<char>(i + 'A'));
		char temp = static_cast<char>(j + 'A');
		if (temp != static_cast<char>(i + 'A')) {
			answer.push_back(temp);
		}
		return answer;
	}
	long index = intermediates[i][j];
	vector<char> v1 = helper(i, index);
	vector<char> v2 = helper(index, j);
	v1.insert(v1.end(), v2.begin() + 1, v2.end());
	return v1;
}

int main(int argc, const char *argv[]) {
	// Make sure the right number of command line arguments exist.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		getline(input_file, line);

		istringstream iss;
		iss.str(line);
		int x;
		if (line_number == 1 && ( !(iss >> x) || (x < 1 || x > 26))) {
			cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
			return 1;
		}

		num_vertices = x;

		long** matrix;
		matrix = make_distance_matrix();

		vector<string> letters;
		for (int i = 0; i < num_vertices; i++) {
			letters.push_back(alphabet[i]);
		}

		line_number++;
		while (getline(input_file, line))
		{
			char split_char = ' ';
			istringstream split(line);
			vector<string> tokens;
			for (string each; getline(split, each, split_char); tokens.push_back(each));

			//Checks if there's 3 inputs on a given line
			if (tokens.size()!=3) {
				cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
				for (int i = 0; i < num_vertices; i++) {
					delete[] matrix[i];
				}
				delete[] matrix;
				return 1;
			}

			//Checks the first input to make sure it's in the valid set of letters or if there's more than one letter
			if (!(find(letters.begin(), letters.end(), tokens[0]) != letters.end()) || tokens[0].size() > 1) {
				cerr << "Error: Starting vertex '" << tokens[0] << "' on line " << line_number << " is not among valid values A-" << alphabet[num_vertices-1] << "." << endl;
				for (int i = 0; i < num_vertices; i++) {
					delete[] matrix[i];
				}
				delete[] matrix;
				return 1;
			}

			//Checks the second input to make sure it's in the valid set of letters or if there's more than one letter
			if (!(find(letters.begin(), letters.end(), tokens[1]) != letters.end()) || tokens[1].size() > 1) {
				cerr << "Error: Ending vertex '" << tokens[1] << "' on line " << line_number << " is not among valid values A-" << alphabet[num_vertices-1] << "." << endl;
				for (int i = 0; i < num_vertices; i++) {
					delete[] matrix[i];
				}
				delete[] matrix;
				return 1;
			}

			//Checks the third input to make sure it's a number or if it's positive
			regex e ("^-?\\d+");
			if(!(regex_match(tokens[2], e)) || stoi(tokens[2]) < 1) {
				cerr << "Error: Invalid edge weight '" << tokens[2] << "' on line " << line_number << "." << endl;
				for (int i = 0; i < num_vertices; i++) {
					delete[] matrix[i];
				}
				delete[] matrix;
				return 1;
			}

			matrix[tokens[0][0]-65][tokens[1][0]-65] = stoi(tokens[2]);

			++line_number;
		}
		// Don't forget to close the file.
		input_file.close();

		for (int i = 0; i < num_vertices; i++) {
			matrix[i][i] = 0;
		}

		//Print out the distance matrix
		string label1 = "Distance matrix:";
		display_table(matrix, label1, false);

		//Create the path lengths and intermediate vertices matrices
		intermediates = make_distance_matrix();
		lengths = make_matrices(matrix);

		//Print out the path lengths matrix
		string label2 = "Path lengths:";
		display_table(lengths, label2, false);

		//Print out the intermediate vertices matrix
		string label3 = "Intermediate vertices:";
		display_table(intermediates, label3, true);


		for (int i = 0; i < num_vertices; i++) {
			for (int j = 0; j < num_vertices; j++) {
				cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: " << flush;
				if (lengths[i][j] == INF) {
					cout << "infinity, path: none" << endl;
					continue;
				} else {
					vector<char> answer = helper(i, j);
					if (answer.size() == 1) {
						cout << "0, path: " << static_cast<char>(i + 'A') << endl;
						continue;
					}

					cout << lengths[i][j] << ", path: " << static_cast<char>(i + 'A') << " -> " << flush;
					for (unsigned int k = 1; k < answer.size(); k++) {
						if (k == answer.size()-1) {
							cout << answer[k] << flush;
						} else {
							cout << answer[k] << " -> " << flush;
						}

					}
					cout << endl;
				}
			}
		}

		for (int i = 0; i < num_vertices; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;


		for (int i = 0; i < num_vertices; i++) {
			delete[] intermediates[i];
		}
		delete[] intermediates;


		return 0;

	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}


	return 0;
}


