#include <bits/stdc++.h>
using namespace std;

bool cmp(const vector<int> &a, const vector<int> &b)
{
    return a[11] > b[11];
}

vector<vector<int>> global_population(20);

void generate_global()
{

    for (int i = 0; i < global_population.size(); i++)
    {
        vector<int> v;
        for (int j = 0; j < 11; j++)
        {
            v.push_back(1 + rand() % 100);
        }
        global_population[i] = v;
    }

    return;
}

vector<vector<int>> generate_chromosomes()
{
    // generate random population (chromosomes)

    // take random indices from the global population
    vector<int> indices(10, 0);
    for (int i = 0; i < indices.size(); i++)
    {
        indices[i] = rand() % 10;
    }

    vector<int> indices_not_there;
    for (int i = 0; i < global_population.size() - indices.size(); i++)
    {
        auto pos = find(indices.begin(), indices.end(), i);
        if (pos == indices.end())
        {
            indices_not_there.push_back(i);
        }
    }

    vector<vector<int>> chromosomes;
    for (int i = 0; i < indices.size(); i++)
    {
        chromosomes.push_back(global_population[indices[i]]);
    }

    return chromosomes;
}

vector<int> calculate_fitness(vector<vector<int>> population_chromosomes)
{

    vector<int> fitness;
    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < population_chromosomes[0].size(); j++)
        {
            sum += population_chromosomes[i][j];
        }
        fitness.push_back(sum);
    }

    return fitness;
}

vector<vector<int>> selection(vector<vector<int>> population_chromosomes, vector<int> fitness)
{
    int first = 0, second = 0;

    sort(population_chromosomes.begin(), population_chromosomes.end(), cmp);

    return population_chromosomes;
}

int main()
{
    int generations = 0;
    cout << "Enter number of generations: ";
    cin >> generations;

    // create global population
    generate_global();

    // obtain the population of chromosomes
    vector<vector<int>> population_chromosomes = generate_chromosomes();
    vector<int> fitness = calculate_fitness(population_chromosomes);

    for (int i = 0; i < population_chromosomes.size(); i++)
    {
        population_chromosomes[i].push_back(fitness[i]);
    }

    // for (int i = 0; i < population_chromosomes.size(); i++)
    // {
    //     for (int j = 0; j < population_chromosomes[0].size(); j++)
    //     {
    //         cout << population_chromosomes[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // selection operation on the given population
    population_chromosomes = selection(population_chromosomes, fitness);
    // top two solutions would be parents

    // selecting best chromosomes as parents

    // crossover operation on the parents

    // mutation operation on the parents

    return 0;
}