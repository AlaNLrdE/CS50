#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startingPopulation;
    int finalPopulation;
    int noOfNewBorns;
    int noOfDeaths;
    int populationByEOY;
    int noOfYears = 0;
    // TODO: Prompt for start size
    do
    {
        startingPopulation = get_int("Starting population: ");
    }
    while (startingPopulation < 9);
    // TODO: Prompt for end size
    do
    {
        finalPopulation = get_int("Final population: ");
    }
    while (finalPopulation < startingPopulation);
    // TODO: Calculate number of years until we reach threshold
    populationByEOY = startingPopulation;
    if (startingPopulation < finalPopulation)
    {
        while (populationByEOY < finalPopulation)
        {
            noOfNewBorns = populationByEOY / 3;
            noOfDeaths = populationByEOY / 4;
            populationByEOY = populationByEOY + noOfNewBorns - noOfDeaths;
            noOfYears++;
        }
    }

    // TODO: Print number of years
    printf("Years: %d\n", noOfYears);
}