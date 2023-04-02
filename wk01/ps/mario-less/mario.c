#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int);

int main(void)
{
    int n = get_height();
    print_pyramid(n);
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (n - (i + 1)); j++)
        {
            printf(" ");  // Print spaces one less than height
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");  // Print #s equal to row number
        }

        printf("\n");
    }

}