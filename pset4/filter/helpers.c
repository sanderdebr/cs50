#include <stdio.h>
#include <math.h>
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
            int avg = round(( (float) blue + (float) green + (float) red) / (float) 3);

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

            int newBlue = round(.272 * (float) originalRed + .534 * (float) originalGreen + .131 * (float) originalBlue);
            int newGreen = round(.349 * (float) originalRed + .686 * (float) originalGreen + .168 * (float) originalBlue);
            int newRed = round(.393 * (float) originalRed + .769 * (float) originalGreen + .189 * (float) originalBlue);

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
    // Loop over every column
        for (int j = 0; j < width; j++)
        {
            // Set each pixel to average RGB
            RGBTRIPLE temp = image[i][width - j - 1];

            image[i][j].rgbtBlue = temp.rgbtBlue;
            image[i][j].rgbtGreen = temp.rgbtGreen;
            image[i][j].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // i = loop over every row
    for (int i = 0; i < height; i++)
    {
    // j = loop over every column
        for (int j = 0; j < width; j++)
        {
            // Array to stores values
            RGBTRIPLE value[9];

            // Check row above
            if (i > 0)
            {
                if (j > 0)
                {
                    value[0] = image[i - 1][j - 1];
                }
                value[1] = image[i - 1][j];
                if (j < width)
                {
                    value[2] = image[i - 1][j + 1];
                }
            }
            // Check row right
            if (j < width)
            {
                value[3] = image[i][j + 1];
                value[4] = image[i + 1][j + 1];
            }
            // Check row bottom
            if (i < height)
            {
                if (j < width)
                {
                    value[5] = image[i + 1][j + 1];
                }
                value[6] = image[i + 1][j];
                if (j > 0)
                {
                    value[7] = image[i + 1][j - 1];
                }
            }
            // Check row left
            if (j > 0)
            {
                value[8] = image[i][j - 1];
            }

            // Calculate avg
            int avgBlue = 0;
            int avgGreen = 0;
            int avgRed = 0;

            for (int k = 0; k < 9; k++)
            {
                avgBlue += value[k].rgbtBlue;
                avgGreen += value[k].rgbtGreen;
                avgRed += value[k].rgbtRed;
            }

            avgBlue = avgBlue / 9;
            avgGreen = avgGreen / 9;
            avgRed = avgRed / 9;

            // Set each pixel to average RGB
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
}
