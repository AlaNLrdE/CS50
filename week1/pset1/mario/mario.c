#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numberOfBlocks;
    int currentLevel;
    int numberOfSpaces;
    int spaceIndex;
    int brickIndex;

    do
    {
        /* ask for the number of blocks of the piramid */
        numberOfBlocks = get_int("Height: ");
        /* ...and keep asking until the number is between 1 and 8 */
    }
    while (numberOfBlocks < 1 || numberOfBlocks > 8);

    /* move between the piramid levels */
    for (currentLevel = 1; currentLevel <= numberOfBlocks; currentLevel++)
    {
        /* print the spaces on the right side */
        numberOfSpaces = numberOfBlocks - currentLevel;
        if (numberOfSpaces > 0)
        {
            for (spaceIndex = 0; spaceIndex < numberOfSpaces; spaceIndex++)
            {
                printf(" ");
            }
        }
        /* print the bricks for each level of the piramid */
        for (brickIndex = 0; brickIndex < currentLevel; brickIndex++)
        {
            printf("#");
        }
        printf("  ");
        /* print the bricks for each level of the piramid on the other side of the crater*/
        for (brickIndex = 0; brickIndex < currentLevel; brickIndex++)
        {
            printf("#");
        }
        printf("\n");
    }
}