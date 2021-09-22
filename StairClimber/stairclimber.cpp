/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Omar Abdelmotaleb
 * Date        : 10/02/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {

	vector< vector<int> > ways;
	if(num_stairs <= 0) {
		vector<int> nothing;
		ways.push_back(nothing);
	}
	else {

		for(int i = 1; i < 4; i++) {
			if(num_stairs >= i) {
				vector< vector<int> > result = get_ways(num_stairs - i);
				for(unsigned int j = 0; j < result.size(); j++) {
					result[j].insert(result[j].begin(), i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}

	}

	return ways;

}

void display_ways(const vector< vector<int> > &ways) {

	cout << ways.size() << " way";
	if(ways.size() != 1) {
		cout << "s";
	}

	cout << " to climb " << ways[0].size() << " stair";
	if(ways[0].size() != 1) {
		cout << "s";
	}

	cout << "." << endl;

	for(unsigned int i = 0; i < ways.size(); i++) {

		if(ways.size() > 9) {
			cout << setw(2) << i + 1;
		}
		else {
			cout << i + 1;
		}
		cout << ". [";
		for(unsigned int j = 0; j < ways[i].size(); j++) {

			cout << ways[i][j];
			if(j + 1 != ways[i].size()) {
				cout << ", ";
			}

		}

		cout << "]" << endl;

	}

}

int main(int argc, char * const argv[]) {

	int stairs;

	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	istringstream iss(argv[1]);
	if( !(iss >> stairs) ) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}



	if(stairs <= 0) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	vector< vector<int> > getways = get_ways(stairs);
	display_ways(getways);

	return 0;

}
