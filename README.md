# Bingo Game README

This is a simple command-line Bingo game written in C++. The game allows players to simulate playing Bingo and win credits by completing specific patterns on their Bingo cards.

## Table of Contents
- [Introduction](#introduction)
- [Game Rules](#game-rules)
- [Code Structure](#code-structure)
- [How to Build and Run](#how-to-build-and-run)
- [License](#license)

## Introduction

Bingo is a popular game of chance where players mark numbers on a Bingo card as they are called out. The goal is to complete specific patterns on the card, such as a line or a full house, to win credits.

This Bingo game provides a simplified version of the classic game, allowing players to experience the excitement of Bingo on their computer.

## Game Rules

- The Bingo card is a 3x5 grid filled with random numbers between 1 and 60.
- Numbers on the card are initially hidden, represented as X's.
- Players start with a certain number of credits.
- In each round, a random Bingo ball is drawn from the remaining ones.
- If the drawn number is on a player's card, it is marked with an X.
- Players can win credits by completing specific patterns on their card:
  - Pattern 1: Mark all numbers in the top row, middle row, and the center cell in the bottom row.
  - Pattern 2: Mark all numbers in the top row, the center cell in the middle row, and all numbers in the bottom row.
- Players can use one credit to continue playing if they run out of Bingo balls.
- The game continues until a player completes one of the winning patterns or runs out of credits.

## Code Structure

The code is structured into three main classes: `BingoCard`, `BingoGame`, and `main`.

- `BingoCard`: Represents a Bingo card with methods for marking numbers, checking for winning patterns, and managing credits.

- `BingoGame`: Manages the Bingo game itself, including drawing balls, checking for wins, and displaying game information.

- `main`: Contains the main entry point for the program, creating and running the Bingo game.

## How to Build and Run

To build and run the Bingo game, you can use the provided Makefile. Follow these steps:

1. Open a terminal window.

2. Navigate to the directory containing the code and Makefile.

3. To build the game, run the following command:
- make

4. To run the game, use the following command:
- make run


5. Follow the on-screen instructions to play the Bingo game.

6. Enjoy the game and try to complete the winning patterns!

## License

This Bingo game is provided under an open-source license. You are free to use, modify, and distribute the code in accordance with the terms of the license. Please refer to the LICENSE file for more details.

