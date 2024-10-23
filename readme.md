Number Guessing Game in C++
Overview
This is a console-based number-guessing game developed in C++ where players attempt to guess a randomly generated number. Players can choose from different difficulty levels, use hints, and compete for high scores on the leaderboard. The game provides feedback after each guess, indicating how many digits are exactly or partially correct.

Features
Difficulty Levels: Easy (3-digit, 10 attempts), Medium (4-digit, 7 attempts), Hard (5-digit, 5 attempts).
Hint System: Players can request hints to reveal specific digits of the number (limited hints per game).
Feedback Mechanism: After each guess, players receive feedback on exact and partial matches.
Score Calculation: Players earn scores based on the number of attempts taken to guess correctly.
Leaderboard: Tracks the top 3 players based on their scores.
How to Run
Prerequisites:

A C++ compiler (e.g., GCC, MinGW, or an IDE like Code::Blocks, Visual Studio).
The code should work on any operating system that supports C++ (Windows, macOS, Linux).
Compilation:

Open the terminal (or command prompt) and navigate to the directory containing the source code.
Use the following command to compile the code:
bash
Copy code
g++ -o number_guessing_game number_guessing_game.cpp
This will create an executable file named number_guessing_game.
Running the Game:

After successful compilation, run the executable:
bash
Copy code
./number_guessing_game   # On macOS or Linux
number_guessing_game.exe  # On Windows
Follow the on-screen instructions to enter your name, select difficulty, and start guessing.
Instructions for Playing
Input Your Name: After starting the game, enter your name to begin.

Select Difficulty: Choose a difficulty level:

1 for Easy (3-digit number, 10 attempts).
2 for Medium (4-digit number, 7 attempts).
3 for Hard (5-digit number, 5 attempts).
Making Guesses:

You will be prompted to enter a number based on the chosen difficulty.
You can type hint during your turn to receive a hint (limited to 2 hints per game).
The game will provide feedback on each guess:
Exact Matches: Digits that are correct and in the correct position.
Partial Matches: Digits that are correct but in the wrong position.
Score and Leaderboard:

Your score is based on the number of attempts you used to guess the number correctly.
The leaderboard shows the top 3 scores. You can try to improve your score by playing again.
Replaying:

After completing a round, you will be asked if you'd like to play again (y/n).
Sample Game Flow
yaml
Copy code
Enter your name: John
Select Difficulty Level:
1. Easy (3-digit number, 10 attempts)
2. Medium (4-digit number, 7 attempts)
3. Hard (5-digit number, 5 attempts)
Enter your choice: 2
I've selected a 4-digit number. You have 7 attempts to guess it correctly. You also have 2 hints.
Enter your 4-digit guess (or type 'hint' for a hint): 1234
Revealed digits: 1###
Exact matches: 1, Partial matches: 1
Attempts remaining: 6
...
Additional Notes
Error Handling: Make sure to input valid guesses. The program will prompt for valid inputs if an incorrect format is entered.
Game Replay: After a game session ends, you have the option to play again or exit.
Future Enhancements
GUI-based interface to improve visual interaction.
Multiplayer mode for competitive play between friends.