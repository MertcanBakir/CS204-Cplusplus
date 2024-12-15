// Mertcan Bakır 30879
#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include <iomanip> // used for put_time
#include <vector>

using namespace std;

mutex coutMutex;  // Mutex for synchronizing console output
mutex gameMutex;  // Mutex for synchronizing game state

bool roundRunning = false;  // Flag to indicate if the round is running
int Target;  // Target number for the current round
bool gameRunning = true;  // Flag to indicate if the game is still running
int correctPlayer = -1;  // Player who guessed correctly

int random_range(const int &min, const int &max) { // Generate random number
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void playerFunction(int playerId, int range1, int range2) {
    while (gameRunning) {

        gameMutex.lock();  // Lock the game mutex
        bool localRoundRunning = roundRunning;
        gameMutex.unlock();  // Unlock the game mutex

        if (localRoundRunning) {
            int guess = random_range(range1, range2);  // Generate a random guess
            time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  // Get the current time

            bool isCorrectGuess = false;

            gameMutex.lock();  // Lock the game mutex
            if (guess == Target && roundRunning) {  // Check if the guess is correct and the round is still running
                roundRunning = false;  // Set the roundRunning flag to false
                correctPlayer = playerId;  // Set the correct player
                isCorrectGuess = true;
            }
            gameMutex.unlock();  // Unlock the game mutex

            coutMutex.lock();  // Lock the cout mutex to synchronize output
            if (isCorrectGuess) {
                cout << "Player with id " << playerId << " guessed " << guess << " correctly at: " << put_time(localtime(&tt), "%X") << endl;
            } else {
                cout << "Player with id " << playerId << " guessed " << guess << " incorrectly at: " << put_time(localtime(&tt), "%X") << endl;
            }
            coutMutex.unlock();  // Unlock the cout mutex

            this_thread::sleep_for(chrono::seconds(1));  // Delay of 1 second for the next guess
        }
    }
}

void hostFunction(int *scores, int numPlayers, int rounds, int range1, int range2) {
    for (int a = 1; a <= rounds; ++a) {  // Loop through the rounds
        coutMutex.lock();  // Lock the cout mutex to synchronize output
        Target = random_range(range1, range2);  // Generate the target number for this round

        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  // Get the current time
        if (a == 1) {  // If it's the first round
            cout << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Game started at: " << put_time(localtime(&tt), "%X") << endl;
            cout << "Round 1 will start 3 seconds later" << endl;
            cout << endl;
            cout << "Target is " << Target << endl;
            cout << endl;
            coutMutex.unlock();
            this_thread::sleep_for(chrono::seconds(3));  // Initial delay of 3 seconds

            gameMutex.lock();
            roundRunning = true;
            gameMutex.unlock();
        } else { // means it is not first round
            cout << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Round " << a << " started at: " << put_time(localtime(&tt), "%X") << endl;
            cout << "Target is " << Target << endl;
            cout << endl;
            coutMutex.unlock();
        }

        gameMutex.lock();  // Lock the game mutex to reset the roundRunning flag
        roundRunning = true;  // Reset the roundRunning flag
        correctPlayer = -1;  // Reset correct player for the new round
        gameMutex.unlock();  // Unlock the game mutex

        while (roundRunning && gameRunning) {
            this_thread::sleep_for(chrono::milliseconds(100));  // Small delay
        }

        // Increment score for the player who guessed correctly
        if (correctPlayer != -1) {
            scores[correctPlayer]++;
        }
    }

    coutMutex.lock();  // Lock the cout mutex to synchronize output
    cout << endl;
    cout << "Game is over!" << endl;
    cout << "Leaderboard:" << endl;
    for (int i = 0; i < numPlayers; ++i) {  // Print the leaderboard
        cout << "Player " << i << " has won " << scores[i] << " times" << endl;
    }
    coutMutex.unlock();  // Unlock the cout mutex

    gameRunning = false;  // Stop all player threads
}

int main() {
    int numPlayers, rounds, range1, range2;
    cout << "Please enter number of players: " << endl;
    cin >> numPlayers;
    while (numPlayers < 1) {  // Re-take input until number of players are greater than 0
        cout << "Number of players cannot be lower than 1!" << endl;
        cin >> numPlayers;
    }

    cout << "Please enter number of rounds: " << endl;
    cin >> rounds;
    while (rounds < 1) {  // Re-take input until rounds are greater than 0
        cout << "Number of rounds cannot be lower than 1!" << endl;
        cin >> rounds;
    }

    cout << "Please enter the randomization range: " << endl;
    cin >> range1 >> range2;
    while (range1 > range2) {  // Re-take the input until lower limit is less than the upper limit
        cout << "Lower bound has to be smaller than or equal to higher bound" << endl;
        cin >> range1 >> range2;
    }

    int* scores = new int[numPlayers]();  // Allocate memory for player scores

    // Create and start player threads
    vector<thread> players;
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(thread(playerFunction, i, range1, range2));
    }

    // Create and start the host thread
    thread host(hostFunction, scores, numPlayers, rounds, range1, range2);
    host.join();

    // Join player threads
    for (int i = 0; i < numPlayers; i++){
        players[i].join();
    }

    delete[] scores;  // Delete the memory allocated for scores

    return 0;
}
