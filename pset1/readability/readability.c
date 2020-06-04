#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Ask user for input string
    char *input = get_string("Text: ");

    // Loop over input
    float letters = 0;
    float words = 0;
    float sentences = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        // Check for letters
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            letters++;
        }
        // Check for words
        if (input[i] == ' ')
        {
            words++;
        }
        // Check for sentences
        if (input[i] == '!' || input[i] == '?' || input[i] == '.')
        {
            sentences++;
        }
    }
    // Fix words
    words++;
    //  Average number of letters per 100 words
    float L = (100 / words) * letters;
    // Average number of sentences per 100 words
    float S = (100 / words) * sentences;

    /* printf("letters: %f\n", letters);
    printf("words: %f\n", words);
    printf("sentences: %f\n", sentences);
    printf("L: %f\n", L);
    printf("S: %f\n", S); */

    // Return Coleman-Liau index formula
    float formula = 0.0588 * L - 0.296 * S - 15.8;
    // Check max grade
    if (formula < 16 && formula >= 1)
    {
        printf("Grade %.0f\n", formula);
    }
    else if (formula < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}