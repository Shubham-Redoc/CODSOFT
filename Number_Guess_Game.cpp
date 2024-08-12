#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

void numberGuess(int t) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));
    
    // Loop for the number of test cases
    for (int i = 0; i < t; ++i) {
        // Generate a random number between 1 and 100
        int randomNumber = rand() % 100 + 1;
        int userGuess = 0;

        cout << "Test case #" << i + 1 << ": Guess the number (between 1 and 100): ";

        // Loop until the user guesses the correct number
        while (userGuess != randomNumber) {
            cin >> userGuess;

            if (userGuess > randomNumber) {
                cout << "Too high! Try again: ";
            } else if (userGuess < randomNumber) {
                cout << "Too low! Try again: ";
            } else {
                cout << "Congratulations! You guessed the correct number!" << endl;
            }
        }
        cout << endl;
    }
}

int main() {
    int t;
    cout << "Enter the number of test cases: ";
    cin >> t;

    numberGuess(t);

    return 0;
}
