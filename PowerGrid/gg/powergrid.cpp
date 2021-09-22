/*******************************************************************************
 * Name    : powergrid.cpp
 * Author  : Omar Abdelmotaleb
 * Version : 1.0
 * Date    : December 18, 2020
 * Description : Computes the minimum set of roads on which to install power lines.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int num_vertices;
int total_length;

// This file will be submitted in the event I don't actually get an algorithm working in time.

int main(int argc, char *argv[]) {

	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}
	
	ifstream input_file(argv[1]);

	if(!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		getline(input_file, line);

		istringstream iss;
		iss.str(line);
		int x;
		if (line_number == 1 && ( !(iss >> x) || (x < 1 || x > 1000))) {
			cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
			return 1;
		}

		num_vertices = x;

		++line_number;

		while(getline(input_file, line)) {
			// Adapted from shortestpaths assignment
			char split_char = ',';
			istringstream split(line);
			vector<string> tokens;
			for(string each; getline(split, each, split_char); tokens.push_back(each));

			if(tokens.size() != 4) {
				cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
				// TODO: Delete stuff here if needed

				return 1;

			}

			istringstream iss;
			int check;
			for(size_t i = 0; i < tokens.size() - 1; i++) {
				iss.clear();
				iss.str(tokens[i]);
				if( !(iss >> check) || check < 1 || (i < 2 && check > num_vertices)) {
					if (i == 0) {
						cerr << "Error: Starting vertex '" << tokens[i] << "' on line " << line_number << " is not among valid values 1-" << num_vertices << "." << endl;
						return 1;
					}
					else if (i == 1) {
						cerr << "Error: Ending vertex '" << tokens[i] << "' on line " << line_number << " is not among valid values 1-" << num_vertices << "." << endl;
						return 1;
					}
					else {
						cerr << "Error: Invalid edge weight '" << tokens[i] << "' on line " << line_number << "." << endl;
						return 1;
					}
				}
			}

			++line_number;

		}
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	return 0;
}
