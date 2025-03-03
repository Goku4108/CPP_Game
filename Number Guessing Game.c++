#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int number = (rand() % 100) + 1;
    // cout << "Generated number is " << number << endl;
    int guess = 0;
    int tries = 0;

    do
    {
        cout << "Enter Guess (1-100): ";
        cin >> guess;
        tries++;

        if (guess < 1 || guess > 100)
        {
            cout << "Please enter a number between 1 and 100." << endl;
            tries--;

            continue;
        }

        if (guess == number)
        {
            cout << "Congratulations! You guessed the number!" << endl;
            cout << "It took you " << tries << " guesses" << endl;
        }
        else if (guess > (number + 2))
        {
            cout << "Guess lower!" << endl;
        }
        else if (guess < (number - 2))
        {
            cout << "Guess higher!" << endl;
        }
        else
        {
            cout << "Too close!" << endl;
        }

    } while (guess != number);

    return 0;
}
