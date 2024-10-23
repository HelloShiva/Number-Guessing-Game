#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <string>
#include <vector>
#include <algorithm> // For sorting
using namespace std;

struct Score
{
    int score;
    int attempts;
    string playerName;
};

void selectDifficulty(int &maxAttempts, int &range, int &numDigits)
{
    int difficulty;
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy (3-digit number, 10 attempts)\n";
    cout << "2. Medium (4-digit number, 7 attempts)\n";
    cout << "3. Hard (5-digit number, 5 attempts)\n";
    cout << "Enter your choice: ";
    cin >> difficulty;

    switch (difficulty)
    {
    case 1:
        maxAttempts = 10;
        range = 900 + 100; // 3-digit range (100-999)
        numDigits = 3;
        break;
    case 2:
        maxAttempts = 7;
        range = 9000 + 1000; // 4-digit range (1000-9999)
        numDigits = 4;
        break;
    case 3:
        maxAttempts = 5;
        range = 90000 + 10000; // 5-digit range (10000-99999)
        numDigits = 5;
        break;
    default:
        cout << "Invalid choice! Defaulting to Medium difficulty.\n";
        maxAttempts = 7;
        range = 9000 + 1000;
        numDigits = 4;
        break;
    }
}

int calculateScore(int attempts, int maxAttempts)
{
    return (maxAttempts - attempts + 1) * 10;
}

void provideHint(string &targetNumber, int &hintCount, const vector<string> &previousGuesses)
{
    if (hintCount > 0)
    {
        // Find an unguessed digit
        vector<int> unguessedIndices;
        for (size_t i = 0; i < targetNumber.length(); i++)
        {
            bool isGuessed = false;
            for (const auto &guess : previousGuesses)
            {
                if (guess[i] == targetNumber[i])
                {
                    isGuessed = true;
                    break;
                }
            }
            if (!isGuessed)
            {
                unguessedIndices.push_back(i);
            }
        }

        if (!unguessedIndices.empty())
        {
            int revealIndex = unguessedIndices[rand() % unguessedIndices.size()];
            cout << "Hint: The digit at position " << revealIndex + 1 << " is " << targetNumber[revealIndex] << ".\n";
            hintCount--;
        }
        else
        {
            cout << "All digits have been guessed. No hint available!\n";
        }
    }
    else
    {
        cout << "Sorry, no hints left!\n";
    }
}

string revealDigits(string guess, string target, int &exactMatches, int &partialMatches)
{
    exactMatches = 0;
    partialMatches = 0;
    string revealed = "";
    string tempTarget = target;

    // Check for exact matches first
    for (int i = 0; i < target.length(); i++)
    {
        if (guess[i] == target[i])
        {
            revealed += guess[i]; // Correct digit
            tempTarget[i] = '#';  // Mark this position as matched
            exactMatches++;
        }
        else
        {
            revealed += '#'; // Mask incorrect digits
        }
    }

    // Check for partial matches
    for (int i = 0; i < guess.length(); i++)
    {
        if (guess[i] != target[i])
        {
            size_t foundPos = tempTarget.find(guess[i]);
            if (foundPos != string::npos)
            {
                partialMatches++;
                tempTarget[foundPos] = '#'; // Mark this position as matched
            }
        }
    }

    return revealed;
}

void updateLeaderboard(vector<Score> &leaderboard, string playerName, int score, int attempts)
{
    leaderboard.push_back({score, attempts, playerName});
    // Sort the leaderboard based on score (highest first)
    sort(leaderboard.begin(), leaderboard.end(), [](Score a, Score b)
         { return a.score > b.score; });

    // Limit to top 3
    if (leaderboard.size() > 3)
    {
        leaderboard.pop_back();
    }
}

void displayLeaderboard(const vector<Score> &leaderboard)
{
    cout << "\n--- Leaderboard ---\n";
    for (size_t i = 0; i < leaderboard.size(); i++)
    {
        cout << i + 1 << ". " << leaderboard[i].playerName << " - Score: " << leaderboard[i].score
             << " (Attempts: " << leaderboard[i].attempts << ")\n";
    }
    cout << "-------------------\n";
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    int maxAttempts, range, numDigits, randomNumber, totalRounds = 0, totalAttempts = 0;
    string targetNumber, guess, playerName;
    vector<Score> leaderboard;
    char playAgain;

    cout << "Enter your name: ";
    cin >> playerName;

    do
    {
        // Select difficulty and setup
        selectDifficulty(maxAttempts, range, numDigits);
        int hintCount = 2; // Limited hints for the game

        // Generate random number within the selected range and convert to string
        randomNumber = rand() % range + (range - 9 * (range / 10));
        targetNumber = to_string(randomNumber);

        cout << "\nYou have selected a " << numDigits << "-digit number.\n";
        cout << "You have " << maxAttempts << " attempts to guess it correctly. You also have " << hintCount << " hints.\n";

        // Game loop
        int attempts = 0, exactMatches = 0, partialMatches = 0;
        bool guessedCorrectly = false;
        totalRounds++;
        vector<string> previousGuesses; // Store previous guesses

        while (attempts < maxAttempts)
        {
            cout << "Enter your " << numDigits << "-digit guess (or type 'hint' for a hint): ";
            cin >> guess;

            if (guess == "hint")
            {
                provideHint(targetNumber, hintCount, previousGuesses); // Pass previous guesses
                continue;
            }

            if (guess.length() != numDigits)
            {
                cout << "Invalid input! Please enter a " << numDigits << "-digit number.\n";
                continue;
            }

            previousGuesses.push_back(guess); // Add the guess to previous guesses
            attempts++;
            totalAttempts++;

            if (guess == targetNumber)
            {
                int score = calculateScore(attempts, maxAttempts);
                cout << "Congratulations! You guessed the number in " << attempts << " attempts!\n";
                cout << "Your score: " << score << "\n";
                updateLeaderboard(leaderboard, playerName, score, attempts);
                guessedCorrectly = true;
                break;
            }
            else
            {
                string revealed = revealDigits(guess, targetNumber, exactMatches, partialMatches);
                cout << "Revealed digits: " << revealed << "\n";
                cout << "Exact matches: " << exactMatches << ", Partial matches: " << partialMatches << "\n";
                cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n";
            }

            if (attempts == maxAttempts)
            {
                cout << "Sorry! You've used all your attempts. The correct number was " << targetNumber << ".\n";
            }
        }

        // Ask if the player wants to play again
        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    // Display game stats
    cout << "Total rounds played: " << totalRounds << "\n";
    cout << "Average attempts per round: " << (totalRounds > 0 ? static_cast<double>(totalAttempts) / totalRounds : 0) << "\n";

    // Show leaderboard
    displayLeaderboard(leaderboard);

    cout << "Thanks for playing!\n";
    return 0;
}
