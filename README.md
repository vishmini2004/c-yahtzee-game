# Yahtzee in C

A console version of Yahtzee written in C. You play 13 rounds against a computer opponent, rolling five dice up to three times per turn and choosing which dice to hold between rolls.

Written as a first-year programming project.

## Features

- Five dice, up to 3 rolls per turn, with the option to hold any dice between rolls
- All 13 scoring categories: Ones to Sixes, Three of a Kind, Four of a Kind, Full House, Small Straight, Large Straight, Yahtzee and Chance
- Each category can only be used once per player
- The game lists the categories you can score in after your final roll, with the potential score for each
- Computer opponent that holds high dice (4 and above) after its first roll and then picks the highest-scoring open category
- Final score comparison at the end of round 13

## How to build and run

You need a C compiler such as GCC.

    gcc yahtzee.c -o yahtzee
    ./yahtzee

On Windows (MinGW), run `yahtzee.exe` instead of `./yahtzee`.

## How to play

1. Each turn the dice are rolled automatically.
2. After roll 1 and roll 2 you are asked whether to hold any dice. Answer `y`, then enter the dice numbers (1 to 5) separated by spaces and finish with `0`.
3. After the third roll, pick a category by its number from the list shown.
4. The computer then takes its turn, and the game continues for 13 rounds.

## Scoring

| Category | Score |
|---|---|
| Ones to Sixes | Sum of the matching dice |
| Three / Four of a Kind | Sum of all five dice |
| Full House | 25 |
| Small Straight (4 in a row) | 30 |
| Large Straight (5 in a row) | 40 |
| Yahtzee (five of a kind) | 50 |
| Chance | Sum of all five dice |

## Concepts practised

Arrays, functions and prototypes, loops and switch statements, random number generation (`rand`/`srand`), simple input handling with `scanf`, and a basic rule-based computer player.

## Possible improvements

- Upper-section bonus and multiple Yahtzee bonuses
- Input validation for invalid menu choices
- A smarter computer strategy
