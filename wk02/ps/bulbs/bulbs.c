#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // get text
    string s = get_string("Message: ");

    for (int letter = 0; letter < strlen(s); letter++)
    {
        // turn letter into decimal
        int decimal = s[letter];

        // turn decimal into binary
        int byte[BITS_IN_BYTE];
        int quotient = decimal;
        for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
        {
            if (quotient % 2)
            {
                byte[i] = 1;
            }
            else
            {
                byte[i] = 0;
            }

            quotient /= 2;
        }

        // print bulbs
        for (int i = 0; i < BITS_IN_BYTE; i++)
        {
            print_bulb(byte[i]);
        }
        printf("\n");
    }

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
