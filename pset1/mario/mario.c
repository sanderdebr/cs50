#include <stdio.h>
#include <cs50.h>

// Making functions available
int get_positive_int(string prompt);

// Main function
int main(void)
{
    // 1. Get height input
    int height = get_positive_int("Height: ");
    string hash = "#";

    // Print row for each height
    for (int i = 0; i < height; i++)
    {
        // Part 1
        // Empty spaces: height - i + 1;
        // Hashes: i + 1
        for (int j = height - i - 1; j > 0; j--)
        {
            printf(" ");
        }

        for (int k = i + 1; k > 0; k--)
        {
            printf("#");
        }

        // Part 2
        printf("  ");

        // Part 3
        for (int k = i + 1; k > 0; k--)
        {
            printf("#");
        }

        // Print row
        printf("\n");
    }
}

// Function that only returns when positive number has been entered, takes prompt as string
int get_positive_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}