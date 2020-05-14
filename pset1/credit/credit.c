#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asking users input
    long number = get_long("Number: ");

    // Defining variables
    int i = 0;
    int even = 0;
    int uneven = 0;

    bool VISA = false;
    bool MASTERCARD = false;
    bool AMEX = false;

    // Get first and second digit
    int first = number / 1000000000000000;
    int second = (number % 1000000000000000) / 100000000000000;

    // If number is 23 characters
    if (first == 0)
    {
        first = number / 100000000000000;
        second = (number % 100000000000000) / 10000000000000;
    }

    // Check first and second numbers for respective creditcard companies
    if (first == 4)
    {
        VISA = true;
    }
    else if (first == 3 && (second == 4 || second == 7))
    {
        AMEX = true;
    }
    else if (first == 5 && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5))
    {
        MASTERCARD = true;
    }

    // Loop over each digit
    while (number)
    {
        i++;
        int result = number % 10;

        // Check for every other number starting from end
        if (i % 2 == 0)
        {
            int multiplied = result * 2;
            while (multiplied)
            {
                even += multiplied % 10;
                multiplied /= 10;
            }
        }
        else
        {
            uneven += result;
        }

        number /= 10;
    }

    int result = even + uneven;

    // Check if last number is a zero to be valid creditcard
    if (result % 10 != 0)
    {
        printf("INVALID\n");
    }
    // Output creditcard result based on booleans value;
    else
    {
        if (VISA)
        {
            printf("VISA\n");
        }
        else if (AMEX)
        {
            printf("AMEX\n");
        }
        else if (MASTERCARD)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}