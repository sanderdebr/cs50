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
        // Check if key contains only alpabetical chars
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if ((key[i] >= 97 && key[i] <= 122) || (key[i] >= 65 && key[i] <= 90))
            {
                // Char contains alphabet
            }
            else
            {
                printf("Key must contain only alphabetical characters.\n");
                return 1;
            }
        }
        // Check for duplicates
        for (int i = 0, n = strlen(key); i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (key[i] == key[j])
                {
                    printf("Key cannot contain duplicates.\n");
                    return 1;
                }
            }
        }
        // Ask for users input
        char *text = get_string("plaintext: ");
        char *result[26];
        char encrypted;
        int position;

        printf("ciphertext: ");
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            // Uppercase char
            if (text[i] >= 'A' && text[i] <= 'Z')
            {
                position = text[i] - 'A';
                encrypted = toupper(key[position]);
                printf("%c", encrypted);
            }
            // Lowercase char
            else if (text[i] >= 'a' && text[i] <= 'z')
            {
                // Get alphabetical position
                position = text[i] - 'a';
                // TODO: Convert key to lowercase;
                encrypted = tolower(key[position]);
                printf("%c", encrypted);
            }
            else
            {
                // print other characters like comma
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
    // None or more than 1 argument is given
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}