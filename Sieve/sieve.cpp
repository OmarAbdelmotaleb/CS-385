/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Omar Abdelmotaleb
 * Date        : 09/18/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {

    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);

	int c = 0;
	if(num_primes_ < primes_per_row) {

		for(int i = 2; i <= limit_; i++) {

			if(is_prime_[i]) {
				cout << i;
			}
			if(is_prime_[i+1]) {
				cout << " ";
			}

		};

	}
	else{

		for(int i = 2; i <= limit_; i++) {

			if(c < primes_per_row) {
				if(is_prime_[i]) {
					cout << setw(max_prime_width) << i;
					// Enters a space after the numbers so long as it's not the last number (max_prime)
					// and is not the number at the end of the line.
					if(i < max_prime_ && c + 1 < primes_per_row) {
						cout << " ";
					}
					c++;
				}
			}
			else {
				c = 0;
				cout << endl;
			}

		};

	}

	cout << endl;


}

int PrimesSieve::count_num_primes() const {

	int c = 0;
	for(int i = 2; i <= limit_; i++) {
		if(is_prime_[i]) {
			c++;
		}
	}
    return c;

}

void PrimesSieve::sieve() {

	// Set everything in is_prime to true.
	for(int i = 2; i <= limit_; i++) {
		is_prime_[i] = true;
	}

	// Sieve algorithm
	for(int i = 2; i <= sqrt(limit_); i++) {
		if(is_prime_[i]) {
			for(int j = i * i; j <= limit_; j += i) {
				is_prime_[j] = false;
			}
		}
	}

	num_primes_ = count_num_primes();

	for(int i = 2; i <= limit_; i++) {
		if(is_prime_[i]) {
			max_prime_ = i;
		}
	}

}

int PrimesSieve::num_digits(int num) {
	// I think this might be unnecessary, but I allowed this method
	// to take in negative numbers too by using abs().
	num = abs(num);
	int c = 0;

	// While digits remain in num, keep taking them off and counting them.
	while(num > 0) {

		num /= 10;
		c++;

	}

    return c;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve primesSieve(limit);
    primesSieve.display_primes();

    return 0;
}
