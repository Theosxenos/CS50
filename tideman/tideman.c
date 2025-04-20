#include "cs50.h"
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_lock_loop(int origin, int from, int to);
int find_pair_winner(int candidate);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) != 0)
        {
            continue;
        }

        ranks[rank] = i;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // preferences[ranks[i]][ranks[i + 1]]++;
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    // for(int t = 0; t < candidate_count; t++)
    // {
    //     printf("%i - %s\n", ranks[t], candidates[ranks[t]]);
    // }

    // for (int i = 0; i < candidate_count - 1; i++)
    // {
    //     preferences[ranks[i]][ranks[i+1]]++;
    // }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            pair pair;
            if (preferences[i][j] > preferences[j][i])
            {
                pair.winner = i;
                pair.loser = j;
                pairs[pair_count] = pair;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pair.winner = j;
                pair.loser = i;
                pairs[pair_count] = pair;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool swap = false;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int winner = pairs[j].winner;
            int loser = pairs[j].loser;
            int votes = preferences[winner][loser] - preferences[loser][winner];

            int next_winner = pairs[j + 1].winner;
            int next_loser = pairs[j + 1].loser;
            int next_votes =
                preferences[next_winner][next_loser] - preferences[next_loser][next_winner];

            if (votes < next_votes)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;

                swap = true;
            }
        }

        if (!swap)
        {
            break;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int from = pairs[i].winner;
        int to = pairs[i + 1].winner;



        locked[from][to] = true;
    }
    return;
}

bool check_lock_loop(int origin, int from, int to)
{
    if (locked[to][from])
    {
        return true;
    }

    if(to == origin)
    {
        return true;
    }

    int next_to = pairs[find_pair_winner(to) + 1].winner;
    bool is_loop = check_lock_loop(origin, to, next_to);

    return false;
}

int find_pair_winner(int candidate)
{
    for(int i = 0;i < candidate_count; i++)
    {
        if(pairs[i].winner == candidate)
        {
            return i;
        }
    }
    return -1;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}
