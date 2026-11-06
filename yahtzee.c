#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROLLS 3
#define SIDES 6

const char* categories[] = {
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
    "Three of a Kind", "Four of a Kind", "Full House",
    "Small Straight", "Large Straight", "Yahtzee", "Chance"
};

// Category scores and used categories for human player
int humanCategoryScores[13] = {0};
int humanUsedCategories[13] = {0};

// Category scores and used categories for computer player
int computerCategoryScores[13] = {0};
int computerUsedCategories[13] = {0};

void rollDice(int dice[], int hold[]);
void printRollingDice(int dice[], int hold[], int rollCount);
void displayAvailableCategories(int dice[], int usedCategories[]);
int calculateScore(int dice[], int category);
void humanTurn(int dice[]);
void computerTurn(int dice[]);
void finalizeGame(int humanScore, int computerScore);
void resetHold(int hold[]);

int main() {
    int humanScore = 0, computerScore = 0;
    int dice[5];

    srand(time(NULL));//initializes the random number generator

    printf("Welcome to Yahtzee!\n");

    for (int round = 1; round <= 13; round++) {
        printf("\n-- Round %d --\n", round);

        printf("\nYour Turn:\n");
        humanTurn(dice);

        printf("\nComputer's Turn:\n");
        computerTurn(dice);
    }

    // Calculate final scores
    for (int i = 0; i < 13; i++) {
        humanScore += humanCategoryScores[i];
        computerScore += computerCategoryScores[i];
    }

    finalizeGame(humanScore, computerScore);

    return 0;
}

void rollDice(int dice[], int hold[]) {
    for (int i = 0; i < 5; i++) {
        if (!hold[i]) {
            dice[i] = (rand() % SIDES) + 1;
        }
    }
}

void printRollingDice(int dice[], int hold[], int rollCount) {
    printf("Roll %d results (excluding held dice):\n", rollCount);
    for (int i = 0; i < 5; i++) {
        if (!hold[i]) {
            printf("Dice %d: %d\n", i + 1, dice[i]);
        }
    }
}

void resetHold(int hold[]) {
    for (int i = 0; i < 5; i++) {
        hold[i] = 0;
    }
}

void displayAvailableCategories(int dice[], int usedCategories[]) {
    printf("Available categories based on your roll:\n");
    for (int i = 0; i < 13; i++) {
        if (!usedCategories[i]) {
            int potentialScore = calculateScore(dice, i);
            if (potentialScore > 0) {
                printf("%d. %s - Potential Score: %d\n", i + 1, categories[i], potentialScore);
            }
        }
    }
}

void humanTurn(int dice[]) {
    int rolls = 0;
    int hold[5] = {0};

    while (rolls < MAX_ROLLS) {
        rollDice(dice, hold);
        printRollingDice(dice, hold, rolls + 1);  // Print only unheld dice

        if (rolls < MAX_ROLLS - 1) {
            char choice;
            printf("Do you want to hold any dice? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y') {
                printf("Enter the dice numbers you want to hold (1-5), separated by spaces (enter 0 to stop):\n");
                int diceNumber;
                while (1) {
                    scanf("%d", &diceNumber);
                    if (diceNumber == 0) break;
                    if (diceNumber >= 1 && diceNumber <= 5) {
                        hold[diceNumber - 1] = 1;
                    }
                }
            }
        }

        rolls++;
    }

    displayAvailableCategories(dice, humanUsedCategories);

    int categoryChoice;//player choosing the category
    printf("Choose a category to apply your score: ");
    scanf("%d", &categoryChoice);
    categoryChoice -= 1;

    if (categoryChoice >= 0 && categoryChoice < 13 && !humanUsedCategories[categoryChoice]) {
        int score = calculateScore(dice, categoryChoice);
        humanCategoryScores[categoryChoice] = score;
        humanUsedCategories[categoryChoice] = 1;
        printf("Score for %s: %d\n", categories[categoryChoice], score);
    } else {
        printf("Invalid category selection. No points for this turn.\n");
    }
}

void computerTurn(int dice[]) {
    printf("Computer's Turn:\n");

    int rolls = 0;
    int hold[5] = {0};

    while (rolls < MAX_ROLLS) {
        rollDice(dice, hold);
        printRollingDice(dice, hold, rolls + 1);  // Print only unheld dice

        //  hold all dice >= 4 in the first roll
        if (rolls == 0) {
            for (int i = 0; i < 5; i++) {
                if (dice[i] >= 4) {
                    hold[i] = 1; // Hold high dice
                }
            }
        }

        rolls++;
    }

    displayAvailableCategories(dice, computerUsedCategories);

    // selecting the best available category
    int bestCategory = -1;
    int highestScore = 0;

    for (int i = 0; i < 13; i++) {
        if (!computerUsedCategories[i]) {
            int score = calculateScore(dice, i);
            if (score > highestScore) {
                highestScore = score;
                bestCategory = i;
            }
        }
    }

    if (bestCategory != -1) {
        computerCategoryScores[bestCategory] = highestScore;
        computerUsedCategories[bestCategory] = 1;
        printf("Computer scores in %s: %d\n", categories[bestCategory], highestScore);
    } else {
        printf("No valid categories available for computer.\n");
    }
}

int calculateScore(int dice[], int category) {
    int score = 0;
    int counts[SIDES + 1] = {0};

    // Count the occurrences of each die value
    for (int i = 0; i < 5; i++) {
        counts[dice[i]]++;
    }

    switch (category) {
        case 0: // Ones
            score = counts[1] * 1;
            break;
        case 1: // Twos
            score = counts[2] * 2;
            break;
        case 2: // Threes
            score = counts[3] * 3;
            break;
        case 3: // Fours
            score = counts[4] * 4;
            break;
        case 4: // Fives
            score = counts[5] * 5;
            break;
        case 5: // Sixes
            score = counts[6] * 6;
            break;
        case 6: // Three of a Kind
            for (int i = 1; i <= SIDES; i++) {
                if (counts[i] >= 3) {
                    score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
                    break;
                }
            }
            break;
        case 7: // Four of a Kind
            for (int i = 1; i <= SIDES; i++) {
                if (counts[i] >= 4) {
                    score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
                    break;
                }
            }
            break;
        case 8: // Full House
            if ((counts[1] == 3 && counts[2] == 2) || (counts[2] == 3 && counts[1] == 2)) {
                score = 25;
            }
            break;
        case 9: // Small Straight
            // Check for 4 consecutive numbers
            if ((counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) ||
                (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1) ||
                (counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1 && counts[6] >= 1)) {
                score = 30;
            }
            break;
        case 10: // Large Straight
            // Check for 5 consecutive numbers
            if ((counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1) ||
                (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1 && counts[6] >= 1)) {
                score = 40;
            }
            break;
        case 11: // Yahtzee
            for (int i = 1; i <= SIDES; i++) {
                if (counts[i] == 5) {
                    score = 50;
                    break;
                }
            }
            break;
        case 12: // Chance
            score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
            break;
    }
    return score;
}

void finalizeGame(int humanScore, int computerScore) {
    printf("\nGame Over!\n");
    printf("Your Total Score: %d\n", humanScore);
    printf("Computer's Total Score: %d\n", computerScore);

    if (computerScore > humanScore) {
        printf("Computer wins!\n");
    } else {
        printf("You win!\n");
    }
}
