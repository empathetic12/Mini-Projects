# Crossword Guessing Game

A simple console-based word guessing game written in C. The player must guess a word letter by letter, with some letters initially revealed. The goal is to complete the word before reaching the maximum number of wrong guesses.

## Features

- **Random Word Selection:** Words are randomly selected from a predefined list.
- **Partially Revealed Words:** Some letters of the word are revealed at the start based on the word length.
- **Tracking Guesses:** The game tracks both total and wrong guesses.
- **Game Over Conditions:** The game ends when the word is fully guessed or when the player exceeds the maximum wrong guesses.

## Requirements

- A C compiler (e.g., GCC).
- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`).

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/crossword-guessing-game.git
    cd crossword-guessing-game
    ```

2. Compile the game using a C compiler:
    ```bash
    gcc -o crossword_game crossword_game.c
    ```

3. Run the game:
    ```bash
    ./crossword_game
    ```

## Game Rules

1. A word is randomly selected from the word bank.
2. Some letters of the word are revealed based on its length.
3. The player is asked to guess a letter.
4. If the guess is correct, the letter is revealed in the word.
5. If the guess is incorrect, the player loses a wrong guess.
6. The game ends when:
    - The word is completely revealed.
    - The player reaches the maximum allowed wrong guesses.
7. At the end of the game, the actual word is revealed.

## Configuration

- **`MAX_WORD_LEN`**: Maximum word length.
- **`MAX_GUESSES`**: Maximum wrong guesses allowed (default is 5).

Feel free to adjust these constants to change the difficulty of the game.

## Example Output




