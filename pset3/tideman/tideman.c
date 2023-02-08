#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void check_cycle(int index);

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
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {

        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    typedef struct
    {
        int pair;
        int votes;
    } strength;

    strength strengths[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strengths[i].pair = i;
        strengths[i].votes = preferences[pairs[i].winner][pairs[i].loser];
    }

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (strengths[j].votes < strengths[j + 1].votes)
            {
                strength temp = strengths[j];
                strengths[j] = strengths[j + 1];
                strengths[j + 1] = temp;
            }
        }
    }

    pair *copy_pairs = malloc(pair_count);

    for (int i = 0; i < pair_count; i++)
    {
        copy_pairs[i] = pairs[i];
    }

    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = copy_pairs[strengths[i].pair];
    }

    free(copy_pairs);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    check_cycle(0);
    return;
}

void check_cycle(int index)
{
    if (index == pair_count)
    {
        return;
    }

    if (index < candidate_count - 1)
    {
        locked[pairs[index].winner][pairs[index].loser] = true;
        check_cycle(index + 1);
    }

    int cycle = 0;
    for (int i = 0; i <= index; i++)
    {
        if (pairs[i].winner == candidate_count - 1)
        {
            if (pairs[i].loser == 0)
            {
                cycle++;
            }
        }

        if (pairs[i].loser == pairs[i].winner + 1)
        {
            cycle++;
        }
    }

    int r_cycle = 0;
    for (int i = 0; i <= index; i++)
    {
        if (pairs[i].winner == 1)
        {
            if (pairs[i].loser == 0)
            {
                r_cycle++;
            }
        }

        if (pairs[i].loser == pairs[i].winner - 1)
        {
            r_cycle++;
        }
    }

    if (cycle != candidate_count && r_cycle != candidate_count)
    {
        locked[pairs[index].winner][pairs[index].loser] = true;
        check_cycle(index + 1);
    }
}

// Print the winner of the election
void print_winner(void)
{
    string winner;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }

            if (i == candidate_count - 1)
            {
                winner = candidates[i];
            }
        }
    }

    printf("%s\n", winner);

    return;
}
