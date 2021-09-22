/*******************************************************************************
 * Name    : powergrid.cpp
 * Author  : Omar Abdelmotaleb
 * Version : 1.0
 * Date    : December 18, 2020
 * Description : Computes the minimum set of roads on which to install power lines using Prim's Algorithm.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

long INF = LONG_MAX;
int num_vertices;
int total_length;

long** make_distance_matrix() {
	long** matrix = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		matrix[i] = new long[num_vertices];
	}

	for (int i = 0; i < num_vertices; i++ ) {
		for (int j = 0; j < num_vertices; j++) {
			matrix[i][j] = 0;
		}
	}

	return matrix;
}

string** make_streets_matrix() {
	string** matrix = new string*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		matrix[i] = new string[num_vertices];
	}

	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			matrix[i][j] = " ";
		}
	}

	return matrix;
}

int minKey(int key[], bool mst[])  
{  
    int min = INT_MAX, min_index;  
  
    for (int v = 0; v < num_vertices; v++)  
        if (mst[v] == false && key[v] < min)  
            min = key[v], min_index = v;  
  
    return min_index;  
}  

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

		long** matrix;
		string** streets;
		matrix = make_distance_matrix();
		streets = make_streets_matrix();

		++line_number;

		while(getline(input_file, line)) {

			// Adapted from ShortestPaths assignment
			char split_char = ',';
			istringstream split(line);
			vector<string> tokens;
			for(string each; getline(split, each, split_char); tokens.push_back(each));

			if(tokens.size() != 4) {
				cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
				for (int i = 0; i < num_vertices; i++) {
					delete[] matrix[i];
					delete[] streets[i];
				}
				delete[] matrix;
				delete[] streets;
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
					}
					else if (i == 1) {
						cerr << "Error: Ending vertex '" << tokens[i] << "' on line " << line_number << " is not among valid values 1-" << num_vertices << "." << endl;
					}
					else {
						cerr << "Error: Invalid edge weight '" << tokens[i] << "' on line " << line_number << "." << endl;
					}
					for (int i = 0; i < num_vertices; i++) {
						delete[] matrix[i];
						delete[] streets[i];
					}
					delete[] matrix;
					delete[] streets;
					return 1;
				}
			}

			int row;
			int col;
			int weight;
			iss.clear();
			iss.str(tokens[0]);
			iss >> row;
			row--;
			iss.clear();
			iss.str(tokens[1]);
			iss >> col;
			col--;
			iss.clear();
			iss.str(tokens[2]);
			iss >> weight;

			matrix[row][col] = weight;
			streets[row][col] = tokens[3];

			++line_number;

		}
		input_file.close();

		if (line_number < 4) {
			cerr << "No solution." << endl;
			for (int i = 0; i < num_vertices; i++) {
				delete[] matrix[i];
				delete[] streets[i];
			}
			delete[] matrix;
			delete[] streets;
			return 1;
		}

		// Base code/logic for Prim's Algorithm adapted from GeeksforGeeks Greedy Algo-5.

		int* parent = new int[num_vertices];
		int* key = new int[num_vertices];
		bool* mst = new bool[num_vertices];
		
		for(int i = 0; i < num_vertices; i++) {
			key[i] = INT_MAX;
			mst[i] = false;
		}
		
		key[0] = 0;
		parent[0] = -1;

		for(int i = 0; i < num_vertices - 1; i++) {
			int u = minKey(key, mst);
			mst[u] = true;
			for(int v = 0; v < num_vertices; v++) {
				if(matrix[u][v] && mst[v] == false && matrix[u][v] < key[v]) {
					parent[v] = u;	
					key[v] = matrix[u][v];
				}
			}
		}

		int total_wire_length = 0;
		for(int i = 1; i < num_vertices; i++) {
			total_wire_length += matrix[parent[i]][i];
		}
		cout << "Total wire length (meters): " << total_wire_length << endl;

		vector<string> work_around_streets;

		for(int i = 1; i < num_vertices; i++) {
			work_around_streets.push_back(streets[parent[i]][i]);
		}

		vector<long> work_around_lengths;
		for(int i = 1; i < num_vertices; i++) {
			work_around_lengths.push_back(matrix[parent[i]][i]);
		}

		sort(work_around_streets.begin(), work_around_streets.end());
		sort(work_around_lengths.begin(), work_around_lengths.end());

		for(int i = 1; i < num_vertices; i++) {
			cout << work_around_streets[i-1] << " [" << work_around_lengths[i-1] << "]" << endl;
		}

		for(int i = 0; i < num_vertices; i++){
			delete[] matrix[i];
			delete[] streets[i];
		}
		
		delete[] matrix;
		delete[] streets;
		delete[] parent;
		delete[] key;
		delete[] mst;

	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	return 0;

}
