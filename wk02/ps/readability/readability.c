#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

string get_text(void);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_grade(int letters, int words, int sentences);
void print_grade(int grade);

int main(void)
{
    string text = get_text();
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    int grade = get_grade(letter_count, word_count, sentence_count);
    print_grade(grade);
}




string get_text(void)
{
    return get_string("Text: ");
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]))
        {
            count += 1;
        }
    }
    return count + 1;  // add one for last word
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count += 1;
        }
    }
    return count;
}

int get_grade(int letters, int words, int sentences)
{
    float letters_per_100 = (float) letters / words * 100;
    float sentences_per_100 = (float) sentences / words * 100;
    int index = round(0.0588 * letters_per_100 - 0.296 * sentences_per_100 - 15.8);
    return index;
}

void print_grade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}