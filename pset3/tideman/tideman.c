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
int compare_pair(const void *a, const void *b);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(void);

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
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
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
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
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
    qsort(pairs, pair_count, sizeof(pair), compare_pair);
    return;
}

int compare_pair(const void *a, const void *b)
{
    const pair *pa = (const pair *)a;
    const pair *pb = (const pair *)b;

    int margin_a = preferences[pa->winner][pa->loser] - preferences[pb->winner][pb->loser];
    int margin_b = preferences[pb->winner][pb->loser] - preferences[pa->winner][pa->loser];

    if (margin_a > margin_b)
    {
        return -1;
    }
    else if (margin_a < margin_b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (check_cycle())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

bool check_cycle(void)
{
    int cycle = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == candidate_count - 1)
        {
            if (locked[i][0] == true)
            {
                cycle++;
            }

            continue;
        }

        if (locked[i][i + 1] == true)
        {
            cycle++;
        }
    }

    int r_cycle = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == 0)
        {
            if (locked[0][candidate_count - 1] == true)
            {
                r_cycle++;
            }

            continue;
        }

        if (locked[i][i - 1] == true)
        {
            r_cycle++;
        }
    }

    if (cycle == candidate_count || r_cycle == candidate_count)
    {
        return true;
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    string winner;
    int numbers = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }

            if (j == candidate_count - 1)
            {
                winner = candidates[i];
                numbers++;
            }
        }
    }

    if (numbers == 1)
    {
        printf("%s\n", winner);
    }

    return;
}
