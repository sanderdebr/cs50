#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average = image[0][0];

    // Loop over every row
    for (int i = 0; i < height; i++)
    {
    // In every row, loop over every pixel
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;
            int avg = (blue + green + red) / 3;

            // Set each pixel to average RGB
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over every row
    for (int i = 0; i < height; i++)
    {
    // In every row, loop over every pixel
        for (int j = 0; j < width; j++)
        {
            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalRed = image[i][j].rgbtRed;

            // Set each pixel to average RGB

            int newBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            int newGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            int newRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;

            if (newBlue <= 255)
            {
                image[i][j].rgbtBlue = newBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            if (newGreen <= 255)
            {
                image[i][j].rgbtGreen = newGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            if (newRed <= 255)
            {
                image[i][j].rgbtRed = newRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over every row
    for (int i = 0; i < height; i++)
    {
    // In every row, loop over every pixel
        for (int j = 0; j < width; j++)
        {
            // Set each pixel to average RGB
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtRed =  image[i][j].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over every row
    for (int i = 0; i < height; i++)
    {
    // In every row, loop over every pixel
        for (int j = 0; j < width; j++)
        {
            // Array to stores values
            RGBTRIPLE value[9];

            // Check row above
            value[0] = image[i - 1][j - 1];
            value[1] = image[i - 1][j];
            value[2] = image[i - 1][j + 1];
            // Check row right
            value[3] = image[i][j + 1];
            value[4] = image[i + 1][j + 1];
            // Check row bottom
            value[5] = image[i + 1][j + 1];
            value[6] = image[i + 1][j];
            value[7] = image[i + 1][j - 1];
            // Check row left
            value[8] = image[i][j - 1];

            // Calculate avg
            int avg = 0;
            for (int k = 0; k < sizeof(value); k++)
            {
                avg += (value[k].rgbtBlue + value[k].rgbtGreen + value[k].rgbtRed) / 3;
            }

            // Set each pixel to average RGB
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}
