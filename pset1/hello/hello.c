#include <stdio.h>
#include <cs50.h>

// Function to ask users name and display on screen
int main(void)
{
    string name = get_string("What is your name? \n");
    printf("hello %s \n", name);
}