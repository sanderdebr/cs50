#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check if 1 argument is given
    if (argc == 2)
    {
        string key = argv[1];
        // Check if exactly 26 chars are given
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        // Ask for users input
        char* text = get_string("plaintext: ");
        char* result[26];
        char encrypted;
        int position;

        printf("ciphertext: ");
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            // Uppercase char
            if (text[i] >= 'A' && text[i] <= 'Z')
            {
                // TODO: something wrong with: get alphabetical position
                position = text[i] - 'A';
                encrypted = key[position];
            }
            // Lowercase char
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                position = text[i] - 'a';
                printf("Char: %c\n", text[i]);
                // Convert key char to lowercase
                encrypted = key[position] - 32;
            }

            result[i] = &encrypted;
            printf("%s", result[i]);

            // TODO: escape \n
        }
        printf("\n");
    }
    // None or more than 1 argument is given
    else {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}