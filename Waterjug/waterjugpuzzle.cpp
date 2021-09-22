/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Omar Abdelmotaleb and Benjamin Singleton
 * Version : 1.0
 * Date    : October 20, 2020
 * Description : Solves water jug puzzle using breadth-first search.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {

    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {

        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();

    }

};


// int a_cap,  b_cap,  and c_cap  are the jug capacities.
// int a_goal, b_goal, and c_goal are the jug goals.
string bfs(int a_cap, int b_cap, int c_cap,
		   int a_goal,int b_goal,int c_goal) {

	queue <State*> q;
	vector<vector<State*>> seen(a_cap+1, vector<State*>(b_cap+1));

	for (auto& row : seen) {
		for (auto& col : row) {
			col = nullptr;
		}
	}


	State* initial = new State(0, 0, c_cap, "Initial");
	State* current = new State(0, 0, c_cap, "Initial");


	q.push(current);

	while (!q.empty()) {

		current = q.front();
		q.pop();

		// Check if current equals goal_state
		if (current->a == a_goal && current->b == b_goal && current->c == c_goal) {

			string result;

			State* copy = current;

			// Starts back-tracing the current state's parents, adding to the output.
			while (current->directions != "Initial") {

				result.insert(0, current->directions);

				current=current->parent;

				if (current->directions != "Initial") {
					result.insert(0,"\n");
				}

			}

			current = copy;
			delete current;
			cout << "Initial state. " << initial->to_string() << endl;

			// Popping Queue q
			while (!(q.empty())) {

				delete q.front();
				q.pop();

			}

			delete initial;

			for (auto& row : seen) {
				for (auto& col : row) {
					delete col;
				}
			}

			return result;

		}

		// See if current has already been seen, otherwise add it to matrix
		if (seen[current->a][current->b] != nullptr) {

			delete current;
			continue;

		} else {
			seen[current->a][current->b] = current;
		}

		// Tries all 6 ways to pour water between the water jugs.

		// Pour A into B
		if ((current->a != 0) && (current->b != b_cap)) {

			int remaining_space_in_b = b_cap - current->b;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_b >= current->a) {

				new_state->b += new_state->a;
				new_state->a -= new_state->a;

				if (current->a == 1) {
					directions << "Pour " << current->a << " gallon from A to B. " << new_state->to_string();
				} else {
					directions << "Pour " << current->a << " gallons from A to B. " << new_state->to_string();
				}

			} else {

				new_state->b += remaining_space_in_b;
				new_state->a -= remaining_space_in_b;

				if (remaining_space_in_b == 1) {
					directions << "Pour " << remaining_space_in_b << " gallon from A to B. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_b << " gallons from A to B. " << new_state->to_string();
				}

			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}

		}

		// Pour A into C
		if ((current->a != 0) && (current->c != c_cap)) {
			int remaining_space_in_c = c_cap - current->c;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_c >= current->a) {
				new_state->c += new_state->a;
				new_state->a -= new_state->a;

				if (current->a == 1) {
					directions << "Pour " << current->a << " gallon from A to C. " << new_state->to_string();
				} else {
					directions << "Pour " << current->a << " gallons from A to C. " << new_state->to_string();
				}


			} else {
				new_state->c += remaining_space_in_c;
				new_state->a -= remaining_space_in_c;

				if (remaining_space_in_c == 1) {
					directions << "Pour " << remaining_space_in_c << " gallon from A to C. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_c << " gallons from A to C. " << new_state->to_string();
				}

			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}

		}

		// Pour B into A
		if ((current->b != 0) && (current->a != a_cap)) {
			int remaining_space_in_a = a_cap - current->a;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_a >= current->b) {
				new_state->a += new_state->b;
				new_state->b -= new_state->b;

				if (current->b == 1) {
					directions << "Pour " << current->b << " gallon from B to A. " << new_state->to_string();
				} else {
					directions << "Pour " << current->b << " gallons from B to A. " << new_state->to_string();
				}

			} else {
				new_state->a += remaining_space_in_a;
				new_state->b -= remaining_space_in_a;

				if (remaining_space_in_a == 1) {
					directions << "Pour " << remaining_space_in_a << " gallon from B to A. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_a << " gallons from B to A. " << new_state->to_string();
				}


			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}

		}

		// Pour B into C
		if ((current->b != 0) && (current->c != c_cap)) {
			int remaining_space_in_c = c_cap - current->c;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_c >= current->b) {
				new_state->c += new_state->b;
				new_state->b -= new_state->b;

				if (current->b == 1) {
					directions << "Pour " << current->b << " gallon from B to C. " << new_state->to_string();
				} else {
					directions << "Pour " << current->b << " gallons from B to C. " << new_state->to_string();
				}

			} else {
				new_state->c += remaining_space_in_c;
				new_state->b -= remaining_space_in_c;

				if (remaining_space_in_c == 1) {
					directions << "Pour " << remaining_space_in_c << " gallon from B to C. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_c << " gallons from B to C. " << new_state->to_string();
				}

			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}

		}

		// Pour C into A
		if ((current->c != 0) && (current->a != a_cap)) {
			int remaining_space_in_a = a_cap - current->a;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_a >= current->c) {
				new_state->a += new_state->c;
				new_state->c -= new_state->c;

				if (current->c == 1) {
					directions << "Pour " << current->c << " gallon from C to A. " << new_state->to_string();
				} else {
					directions << "Pour " << current->c << " gallons from C to A. " << new_state->to_string();
				}

			} else {
				new_state->a += remaining_space_in_a;
				new_state->c -= remaining_space_in_a;

				if (remaining_space_in_a == 1) {
					directions << "Pour " << remaining_space_in_a << " gallon from C to A. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_a << " gallons from C to A. " << new_state->to_string();
				}

			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}

		}

		// Pour C into B
		if ((current->c != 0) && (current->b != b_cap)) {
			int remaining_space_in_b = b_cap - current->b;
			ostringstream directions;
			string temp = "temp";
			State* new_state = new State(current->a, current->b, current->c, temp);
			new_state->parent = current;

			if(remaining_space_in_b >= current->c) {
				new_state->b += new_state->c;
				new_state->c -= new_state->c;

				if (current->b == 1) {
					directions << "Pour " << current->b << " gallon from C to B. " << new_state->to_string();
				} else {
					directions << "Pour " << current->b << " gallons from C to B. " << new_state->to_string();
				}

			} else {
				new_state->b += remaining_space_in_b;
				new_state->c -= remaining_space_in_b;

				if (remaining_space_in_b == 1) {
					directions << "Pour " << remaining_space_in_b << " gallon from C to B. " << new_state->to_string();
				} else {
					directions << "Pour " << remaining_space_in_b << " gallons from C to B. " << new_state->to_string();
				}
			}

			string direct = directions.str();
			new_state->directions = direct;

			if (seen[new_state->a][new_state->b] != nullptr) {
				delete new_state;
			} else {
				q.push(new_state);
			}
		}

	}


	delete initial;

	for (auto& row : seen) {
		for (auto& col : row) {
			delete col;
		}
	}

	return "No solution.";

}


int main(int argc, char * const argv[]) {
	int CA, CB, CC, GA, GB, GC;
	istringstream iss;

	if (argc != 7) {

		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;

	}

	// Checks to see if each input is acceptable for the capacities.

	// Checks cap A
	iss.str(argv[1]);
	if (!(iss >> CA) || CA < 0) {

		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;

	}
	iss.clear();

	// Checks cap B
	iss.str(argv[2]);
	if (!(iss >> CB) || CB < 0) {

		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;

	}
	iss.clear();

	// Checks cap C
	iss.str(argv[3]);
	if (!(iss >> CC) || CC <= 0) {

		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;

	}
	iss.clear();


	// Checks to see if each input is acceptable for the goals.

	// Checks goal A
	iss.str(argv[4]);
	if (!(iss >> GA) || GA < 0) {

		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;

	}
	iss.clear();

	// Checks goal B
	iss.str(argv[5]);
	if (!(iss >> GB) || GB < 0) {

		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;

	}
	iss.clear();

	// Checks goal C
	iss.str(argv[6]);
	if (!(iss >> GC) || GC < 0) {

		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;

	}
	iss.clear();


	// Checks to see if goals exceed capacities.

	if (CA < GA) {

		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;

	}

	if (CB < GB) {

		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;

	}

	if (CC < GC) {

		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;

	}

	if (CC != (GA + GB + GC)) {

		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;

	}

	string answer = bfs(CA, CB, CC, GA, GB, GC);
	cout << answer << endl;

    return 0;

}
