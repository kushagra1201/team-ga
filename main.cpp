#include <bits/stdc++.h>
int features = 4;
using namespace std;

vector<vector<int>> gen_chromosomes()
{
    // generate random population (chromosomes)
    // consider each feature range and generate random values into a vector
    vector<vector<int>> pop(11, vector<int>(features, 0));
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < features; j++)
        {
            pop[i][j] = 1 + rand() % 100;
        }
    }

    return pop;
}

int main()
{
    int generations = 0;
    cout << "Enter number of generations: ";
    cin >> generations;

    // obtain the population of chromosomes
    vector<vector<int>> population = gen_chromosomes();

    // reproduction operation on the given population

    // selecting best chromosomes as parents

    // crossover operation on the parents

    // mutation operation on the parents

    return 0;
}