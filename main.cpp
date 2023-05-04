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

int calculate_variance(vector<int> v)
{
    double sum = accumulate(begin(v), end(v), 0);
    double m = sum / v.size();

    double accum = 0;
    for_each(begin(v), end(v), [&](const double d)
             { accum += (d - m) * (d - m); });

    double stdev = sqrt(accum / (v.size() - 1));

    int var = pow(stdev, 2);

    return (var * 100) / 40;
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

vector<vector<int>> calculate_fitness(vector<vector<int>> population_chromosomes, double skill_weight, double cost_weight, double demog_weight)
{

    int skills_sum = 0, demog_sum = 0, cost_sum = 0;

    skill_weight /= 100;
    cost_weight /= 100;
    demog_weight /= 100;

    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        vector<int> v;
        for (int j = 0; j < population_chromosomes[0].size() - 1; j++)
        {
            skills_sum += global_skills[population_chromosomes[i][j]];
            cost_sum += global_cost[population_chromosomes[i][j]];
            v.push_back(global_demog[population_chromosomes[i][j]]);
        }
        int variance_demog = (calculate_variance(v) * 40) / 100;
        int cost_effectiveness = (cost_sum * 100) / skills_sum;

        population_chromosomes[i][11] = (double)(skill_weight * (skills_sum / 110)) + (double)(demog_weight * variance_demog) + (double)(cost_weight * (cost_effectiveness));
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

    cout << "Population of Players: " << endl;
    for (int i = 0; i < 100; i++)
    {
        cout << "Player No. " << i + 1 << " - " << global_skills[i] << " " << global_demog[i] << " " << global_cost[i] << endl;
    }

    int skill_weight = 0, cost_weight = 0, demog_weight = 0;
    cout << "Enter Skill Weight: ";
    cin >> skill_weight;
    cout << "Enter Demographic Weight: ";
    cin >> demog_weight;
    cout << "Enter Cost Weight: ";
    cin >> cost_weight;

    cout << endl;

    while (curr < generations)
    {
        population_chromosomes = calculate_fitness(population_chromosomes, skill_weight, cost_weight, demog_weight);

        // selection operation on the given population
        population_chromosomes = selection(population_chromosomes);
        // selecting best chromosomes as parents

        // crossover operation on the parents - single point crossover
        population_chromosomes = crossover(population_chromosomes);
        population_chromosomes = calculate_fitness(population_chromosomes, skill_weight, cost_weight, demog_weight);

        // mutation operation on the parents - single point mutation
        population_chromosomes = mutation(population_chromosomes);
        population_chromosomes = calculate_fitness(population_chromosomes, skill_weight, cost_weight, demog_weight);

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

        cout << "Generation Best: " << global_best(population_chromosomes) << endl
             << endl;

        curr++;
    }

    // obtain the population of chromosomes
    return 0;
}