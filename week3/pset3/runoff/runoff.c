#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    bool boRet = false;
    bool boFinished = false;
    int i = 0;

    do
    {
        if (!strcmp(name, candidates[i].name))
        {
            boFinished = true;
            boRet = true;
            preferences[voter][rank] = i;
        }
        else
        {
            i++;
            if (i >= candidate_count)
            {
                boFinished = true;
            }
        }
    }
    while (false == boFinished);

    return boRet;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    bool finished;
    int candidate_index;

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    for (int i = 0; i < voter_count; i++)
    {
        candidate_index = 0;
        finished = false;
        do
        {
            if (candidates[preferences[i][candidate_index]].eliminated != true)
            {
                candidates[preferences[i][candidate_index]].votes++;
                finished = true;
            }
            else
            {
                candidate_index++;
            }
        }
        while (finished != true);
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int votes_to_win = (voter_count / 2) + 1; 
    bool boRet = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= votes_to_win)
        {
            printf("%s\n", candidates[i].name);
            boRet = true;
            break;
        }
    }

    return boRet;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = 0xFFFF;

    // Loop through every candidate to try to find the minimum
    // number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        // consider only the non eliminated candidates
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
            
        }
        else
        {
            /* do nothing */
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // return value will be true (tie) unless there's a candidate
    // with a greater number of votes
    bool tie = true;

    for (int i = 0; i < candidate_count; i++)
    {
        // dont even bother with the eliminated candidates...
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > min)
            {
                tie = false;
            }
        }
    }

    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // disregard the ones that are already eliminated
        if (candidates[i].eliminated == false)
        {
            // eliminate the candidate if the number of votes is equal
            // to the minimum number of votes.
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
}

