#include <bits/stdc++.h>
using namespace std;

bool cmp(const vector<int> &a, const vector<int> &b)
{
    return a[11] > b[11];
}

vector<int> global_skills(100);
vector<int> global_demog(100);
vector<int> global_cost(100);

void generate_skills()
{
    for (int i = 0; i < global_skills.size(); i++)
    {
        int skill = 1 + rand() % 100;
        global_skills[i] = skill;
    }

    return;
}

void generate_demog()
{
    for (int i = 0; i < global_demog.size(); i++)
    {
        int demog = 18 + rand() % 23;
        global_demog[i] = demog;
    }

    return;
}

void generate_cost()
{
    for (int i = 0; i < global_cost.size(); i++)
    {
        int cost = rand() % 100;
        global_cost[i] = cost;
    }

    return;
}

vector<vector<int>> generate_chromosomes()
{
    // generate random population (chromosomes)
    vector<vector<int>> chromosomes(10, vector<int>(12, 0));
    // take random indices from the global population
    for (int i = 0; i < chromosomes.size(); i++)
    {
        for (int j = 0; j < 11; j++)
        {
            int player_index = rand() % 100;
            chromosomes[i][j] = player_index;
        }
    }

    return chromosomes;
}

vector<vector<int>> calculate_fitness(vector<vector<int>> population_chromosomes)
{

    int skills_sum = 0, demog_sum = 0, cost_sum = 0;

    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        for (int j = 0; j < population_chromosomes[0].size() - 1; j++)
        {
            skills_sum += global_skills[population_chromosomes[i][j]];
            demog_sum += global_demog[population_chromosomes[i][j]];
            cost_sum += global_cost[population_chromosomes[i][j]];
        }

        population_chromosomes[i][11] = (0.5 * skills_sum) + (0.1 * demog_sum) + (0.4 * cost_sum);
    }

    return population_chromosomes;
}

vector<vector<int>> selection(vector<vector<int>> population_chromosomes)
{
    int first = 0, second = 0;

    sort(population_chromosomes.begin(), population_chromosomes.end(), cmp);

    return population_chromosomes;
}

vector<vector<int>> crossover(vector<vector<int>> population_chromosomes)
{
    int prob_crossover = rand() % 10;

    for (int i = 0; i < population_chromosomes.size(); i += 2)
    {
        for (int j = prob_crossover; j < population_chromosomes[0].size() - 1; j++)
        {
            int temp = population_chromosomes[i][j];
            population_chromosomes[i][j] = population_chromosomes[i + 1][j];
            population_chromosomes[i + 1][j] = temp;
        }
    }

    return population_chromosomes;
}

vector<vector<int>> mutation(vector<vector<int>> population_chromosomes)
{
    int prob_mutation = rand() % 10;

    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        int external_player_index = rand() % 100;
        population_chromosomes[i][prob_mutation] = external_player_index;
    }

    return population_chromosomes;
}

int global_best(vector<vector<int>> population_chromosomes)
{
    int maximum = 0;

    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        if (maximum < population_chromosomes[i][11])
        {
            maximum = population_chromosomes[i][11];
        }
    }

    return maximum;
}

int main()
{
    int generations = 0, curr = 0;
    cout << "Enter number of generations: ";
    cin >> generations;

    // create global population
    generate_skills();
    generate_cost();
    generate_demog();
    vector<vector<int>> population_chromosomes = generate_chromosomes();

    while (curr < generations)
    {
        population_chromosomes = calculate_fitness(population_chromosomes);

        // selection operation on the given population
        population_chromosomes = selection(population_chromosomes);
        // selecting best chromosomes as parents

        // crossover operation on the parents - single point crossover
        population_chromosomes = crossover(population_chromosomes);
        population_chromosomes = calculate_fitness(population_chromosomes);

        // mutation operation on the parents - single point mutation
        population_chromosomes = mutation(population_chromosomes);
        population_chromosomes = calculate_fitness(population_chromosomes);

        // reproduction of population with better chromosomes
        // population_chromosomes = reproduction(population_chromosomes);

        cout << "Generation: " << curr + 1 << endl;
        for (int i = 0; i < population_chromosomes.size(); i++)
        {
            for (int j = 0; j < population_chromosomes[0].size(); j++)
            {
                cout << population_chromosomes[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << global_best(population_chromosomes) << endl;

        curr++;
    }

    // obtain the population of chromosomes
    return 0;
}