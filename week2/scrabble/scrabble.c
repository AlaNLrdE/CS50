#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define cnstLowerToCap 32
#define cnstLetterToValueIndex 65

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Player 1 wins if his score is bigger
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        // Player 2 wins if his score is bigger
        printf("Player 2 wins!\n");
    }
    else 
    {
        // But is a tie if their scores are the same
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int i = 0;
    int score = 0;
    char tmpChar = '\0';
    // TODO: Compute and return score for string
    // Iterate while the end of the string
    while (word[i] != '\0')
    {
        tmpChar = word[i];
        // Convert lower to capital case by substracting 32i
        if (tmpChar >= 'a' && tmpChar <= 'z') 
        {
            tmpChar -= cnstLowerToCap;
        }
        // Covert capital case to score array index by substracting 65i
        if (tmpChar >= 'A' && tmpChar <= 'Z')
        {
            tmpChar -= cnstLetterToValueIndex;
            // Accumulate the points in the variable score
            score += POINTS[(int)tmpChar];
        } 
        i++;
    }
    return score;
}