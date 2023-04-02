#include <cs50.h>
#include <stdio.h>

int get_start_size(void);
int get_end_size(int start_size);
int get_years(int start_size, int end_size);
void print_years(int years);

int main(void)
{
    int start_size = get_start_size();
    int end_size = get_end_size(start_size);
    int years = get_years(start_size, end_size);
    print_years(years);
}

int get_start_size(void)
{
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);
    return n;
}

int get_end_size(int start_size)
{
    int n;
    do
    {
        n = get_int("End size: ");
    }
    while (n < start_size);
    return n;
}

int get_years(int start_size, int end_size)
{
    int years = 0;
    int population = start_size;
    while (population < end_size)
    {
        population = population + (population / 3) - (population / 4);
        years += 1;
    }
    return years;
}

void print_years(int years)
{
    printf("Years: %i\n", years);
}