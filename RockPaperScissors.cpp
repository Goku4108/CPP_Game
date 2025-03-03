#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

class RockPaperScissorsGame
{
private:
    vector<string> choices;
    string toLowerCase(const string &str) const
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    string generateRandomChoice() const
    {
        random_device rd;
        mt19937 engine(rd());
        uniform_int_distribution<> dist(0, choices.size() - 1);

        size_t index = dist(engine);
        return choices[index];
    }

    string determineWinner(const string &userChoice, const string &computerChoice) const
    {
        if (userChoice == computerChoice)
        {
            return "It's a tie!";
        }
        if ((userChoice == "rock" && computerChoice == "scissors") ||
            (userChoice == "scissors" && computerChoice == "paper") ||
            (userChoice == "paper" && computerChoice == "rock"))
        {
            return "You win!";
        }
        return "You lose!";
    }

public:
    RockPaperScissorsGame() : choices{"rock", "paper", "scissors"} {}

    void play()
    {
        while (true)
        {
            string userChoice;
            cout << "Enter your choice (Rock, Paper, or Scissors): ";
            cin >> userChoice;

            userChoice = toLowerCase(userChoice);

            auto it = find(choices.begin(), choices.end(), userChoice);
            if (it == choices.end())
            {
                cout << "Invalid choice. Please enter rock, paper, or scissors." << endl;
                continue;
            }

            string computerChoice = generateRandomChoice();
            cout << "Computer chose: " << computerChoice << endl;

            string result = determineWinner(userChoice, computerChoice);
            cout << result << endl;

            if (result == "You lose!")
            {
                cout << "Thank you for playing!" << endl;
                break;
            }
        }
    }
};

int main()
{
    RockPaperScissorsGame game;
    game.play();
    return 0;
}
