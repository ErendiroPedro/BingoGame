#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <cstdlib>
#include <set>

const int MAX_BALL_NUMBER = 60;
const int MAX_CREDITS = 1;
const int PATTERN1_PRIZE = 10;
const int PATTERN2_PRIZE = 50;
const int MAX_DRAWN_BALLS = 30;

// Generate a unique random number within a given set
int generateUniqueNumber(std::set<int>& drawnNumbers) {
    int num;
    do {
        num = std::rand() % MAX_BALL_NUMBER + 1;
    } while (drawnNumbers.count(num) > 0);
    drawnNumbers.insert(num);
    return num;
}

class BingoCard {
private:
    std::array<std::array<int, 5>, 3> numbersMatrix;
    std::set<int> markedNumbers;
    int credits = MAX_CREDITS;

    // Check if the card has Pattern 1 win
    bool isPattern1Win() {
        bool row1 = (numbersMatrix[0][0] == -1) && (numbersMatrix[0][1] == -1) && (numbersMatrix[0][2] == -1) && (numbersMatrix[0][3] == -1) && (numbersMatrix[0][4] == -1);
        bool row2 = (numbersMatrix[1][1] == -1) && (numbersMatrix[1][2] == -1) && (numbersMatrix[1][3] == -1);
        bool row3 = (numbersMatrix[2][2] == -1);

        if (row1 && row2 && row3) {
            std::cout << "Bingo Pattern 1 Win!" << std::endl;
            addCredits(PATTERN1_PRIZE);
            return true;
        }

        return false;
    }

    // Check if the card has Pattern 2 win
    bool isPattern2Win() {
        bool row1 = (numbersMatrix[0][0] == -1) && (numbersMatrix[0][1] == -1) && (numbersMatrix[0][2] == -1) && (numbersMatrix[0][3] == -1) && (numbersMatrix[0][4] == -1);
        bool row2 = (numbersMatrix[1][2] == -1);
        bool row3 = (numbersMatrix[2][0] == -1) && (numbersMatrix[2][1] == -1) && (numbersMatrix[2][2] == -1) && (numbersMatrix[2][3] == -1) && (numbersMatrix[2][4] == -1);

        if (row1 && row2 && row3) {
            std::cout << "Bingo Pattern 2 Win!" << std::endl;
            addCredits(PATTERN2_PRIZE);
            return true;
        }

        return false;
    }

public:
    BingoCard() {
        std::srand(std::time(0));
        std::set<int> drawnNumbers;
        for (int i = 0; i < numbersMatrix.size(); i++) {
            for (int j = 0; j < numbersMatrix[i].size(); j++) {
                numbersMatrix[i][j] = generateUniqueNumber(drawnNumbers);
            }
        }
    }

    // Mark a number on the bingo card as called
    void markNumber(int num) {
        for (auto& row : numbersMatrix) {
            for (int& cell : row) {
                if (cell == num) {
                    cell = -1;
                }
            }
        }
    }

    // Check if the card has any winning pattern
    bool isBingo() {
        return isPattern1Win() | isPattern2Win(); // Logical OR Open circuit
    }

    // Use one credit
    int useCredits() {
        if (credits > 0) {
            credits--;
        }
        return credits;
    }

    // Add credits to the card
    void addCredits(int num) {
        credits += num;
    }

    // Print the current state of the bingo card
    void printCard() const {
        std::cout << std::endl << std::endl;
        for (const auto& row : numbersMatrix) {
            for (int num : row) {
                std::cout << (num == -1 ? "X" : std::to_string(num)) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Print the player's current credit balance
    void printPlayerCredit() const {
        std::cout << "Player credits: " << credits << std::endl;
    }
};

class BingoGame {
private:
    std::vector<int> balls; // Random bingo balls (1-MAX_BALL_NUMBER)
    std::vector<int> ballsDrawn;
    BingoCard player;

    // Reset the bingo balls for a new game
    void resetBalls() {
        std::srand(std::time(0));
        std::set<int> drawnBalls;
        while (balls.size() < MAX_DRAWN_BALLS) {
            int num = generateUniqueNumber(drawnBalls);
            balls.push_back(num);
        }
    }

    // Draw a bingo ball from the remaining ones
    void drawBall() {
        int drawnBallIndex = std::rand() % balls.size();
        int drawnNumber = balls[drawnBallIndex];
        ballsDrawn.push_back(drawnNumber);
        balls.erase(balls.begin() + drawnBallIndex);

        printCurrentBall(drawnNumber);
        printPastBalls();

        player.markNumber(drawnNumber);
        player.printCard();
    }

    // Check if the player has won
    bool checkWin() {
        return player.isBingo();
    }

    // Display information at the start of each round
    void displayRoundInfo(int round) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Round " << round << std::endl;
        player.printPlayerCredit();
        printPossibleBalls();
    }

    // Print the list of possible bingo balls
    void printPossibleBalls() {
        std::cout << std::endl << "Possible balls: ";
        for (int ball : balls) {
            std::cout << ball << " ";
        }
        std::cout << std::endl;
    }

    // Print the list of past drawn bingo balls
    void printPastBalls() {
        std::cout << "Past balls: ";
        for (auto& ball : ballsDrawn) {
            std::cout << std::to_string(ball) << " ";
        }
        std::cout << std::endl;
    }

    // Print the currently drawn bingo ball
    void printCurrentBall(int drawnNumber) {
        std::cout << "Current ball: " << std::to_string(drawnNumber) << std::endl;
    }

public:
    BingoGame() {
        resetBalls();
    }

    // Play the Bingo game
    void playGame() {
        std::cout << std::endl;
        bool isBingo = false;
        bool hasCredits = true;
        int round = 1;

        while (!isBingo && hasCredits) {
            displayRoundInfo(round);

            if (balls.empty()) {
                hasCredits = player.useCredits() > 0;
                if (!hasCredits) {
                    std::cout << "Out of credits. Game over!" << std::endl;
                    break;
                }
            }

            drawBall();

            isBingo = checkWin();

            if (isBingo) {
                std::cout << "Bingo! You win!" << std::endl;
            }

            std::cout << std::endl;

            std::cout << "Press Enter to continue...";
            std::cin.get(); // Wait for player input

            round++;
        }
    }
};

int main() {
    BingoGame game;
    game.playGame();
    return 0;
}
