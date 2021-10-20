#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// function prototypes
int count_letters(string txt, int len);
int count_words(string txt, int len);
int count_sentences(string txt, int len);

int main(void)
{
    string text = get_string("Text: ");

    // Formula used for caluculation :-
    // index = 0.0588 * L - 0.296 * S - 15.8
    // Where L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.

    int index, length = strlen(text);
    float L, S;

    L = ((float) count_letters(text, length) / count_words(text, length)) * 100;
    S = ((float) count_sentences(text, length) / count_words(text, length)) * 100;

    index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string txt, int len)
{
    int letters = 0;
    for (int i = 0; i < len; i++)
    {
        // Alphabet occurs, increment letters
        if (isalpha(txt[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string txt, int len)
{
    int words = 0, space_flag = 0;
    for (int i = 0; i < len; i++)
    {
        // Space occurs reset space_flag
        if (isspace(txt[i]))
        {
            space_flag = 0;
        }

        // If character is first letter of word, increment words
        if (isalpha(txt[i]) && space_flag == 0)
        {
            words++;
            space_flag++;
        }
    }
    return words;
}

int count_sentences(string txt, int len)
{
    int sentences = 0;
    for (int i = 0; i < len; i++)
    {
        // Sentence ended increment sentences
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}