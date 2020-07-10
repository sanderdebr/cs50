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
        int halfWidth = round( (float) 1/2 * width);
        for (int j = 0; j < width; j++)
        {

            while (j < halfWidth)
            {
                // Set each pixel to average RGB
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = temp;
                break;
            }

        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i + 1][j].rgbtRed
                + ogImage[i][j + 1].rgbtRed + ogImage[i + 1][j + 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i + 1][j].rgbtGreen
                + ogImage[i][j + 1].rgbtGreen + ogImage[i + 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i + 1][j].rgbtBlue
                + ogImage[i][j + 1].rgbtBlue + ogImage[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i + 1][j].rgbtRed
                + ogImage[i][j - 1].rgbtRed + ogImage[i + 1][j - 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i + 1][j].rgbtGreen
                + ogImage[i][j - 1].rgbtGreen + ogImage[i + 1][j - 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i + 1][j].rgbtBlue
                + ogImage[i][j - 1].rgbtBlue + ogImage[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i][j - 1].rgbtRed + ogImage[i][j + 1].rgbtRed
                + ogImage[i + 1][j].rgbtRed + ogImage[i + 1][j - 1].rgbtRed + ogImage[i + 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i][j - 1].rgbtGreen + ogImage[i][j + 1].rgbtGreen
                + ogImage[i + 1][j].rgbtGreen + ogImage[i + 1][j - 1].rgbtGreen + ogImage[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i][j - 1].rgbtBlue + ogImage[i][j + 1].rgbtBlue
                + ogImage[i + 1][j].rgbtBlue + ogImage[i + 1][j - 1].rgbtBlue + ogImage[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i - 1][j].rgbtRed
                + ogImage[i][j + 1].rgbtRed + ogImage[i - 1][j + 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i - 1][j].rgbtGreen
                + ogImage[i][j + 1].rgbtGreen + ogImage[i - 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i - 1][j].rgbtBlue
                + ogImage[i][j + 1].rgbtBlue + ogImage[i - 1][j + 1].rgbtBlue) / 4.0);
            }
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i - 1][j].rgbtRed + ogImage[i + 1][j].rgbtRed
                + ogImage[i][j + 1].rgbtRed + ogImage[i - 1][j + 1].rgbtRed + ogImage[i + 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i - 1][j].rgbtGreen + ogImage[i + 1][j].rgbtGreen
                + ogImage[i][j + 1].rgbtGreen + ogImage[i - 1][j + 1].rgbtGreen + ogImage[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i - 1][j].rgbtBlue + ogImage[i + 1][j].rgbtBlue
                + ogImage[i][j + 1].rgbtBlue + ogImage[i - 1][j + 1].rgbtBlue + ogImage[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i - 1][j].rgbtRed
                + ogImage[i][j - 1].rgbtRed + ogImage[i - 1][j - 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i - 1][j].rgbtGreen
                + ogImage[i][j - 1].rgbtGreen + ogImage[i - 1][j - 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i - 1][j].rgbtBlue
                + ogImage[i][j - 1].rgbtBlue + ogImage[i - 1][j - 1].rgbtBlue) / 4.0);
            }
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i][j - 1].rgbtRed + ogImage[i][j + 1].rgbtRed
                + ogImage[i - 1][j].rgbtRed + ogImage[i - 1][j - 1].rgbtRed + ogImage[i - 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i][j - 1].rgbtGreen + ogImage[i][j + 1].rgbtGreen
                + ogImage[i - 1][j].rgbtGreen + ogImage[i - 1][j - 1].rgbtGreen + ogImage[i - 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i][j - 1].rgbtBlue + ogImage[i][j + 1].rgbtBlue
                + ogImage[i - 1][j].rgbtBlue + ogImage[i - 1][j - 1].rgbtBlue + ogImage[i - 1][j + 1].rgbtBlue) / 6.0);
            }
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i - 1][j].rgbtRed + ogImage[i + 1][j].rgbtRed
                + ogImage[i][j - 1].rgbtRed + ogImage[i - 1][j - 1].rgbtRed + ogImage[i + 1][j - 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i - 1][j].rgbtGreen + ogImage[i + 1][j].rgbtGreen
                + ogImage[i][j - 1].rgbtGreen + ogImage[i - 1][j - 1].rgbtGreen + ogImage[i + 1][j - 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i - 1][j].rgbtBlue + ogImage[i + 1][j].rgbtBlue
                + ogImage[i][j - 1].rgbtBlue + ogImage[i - 1][j - 1].rgbtBlue + ogImage[i + 1][j - 1].rgbtBlue) / 6.0);
            }
            else
            {
                image[i][j].rgbtRed = round((ogImage[i][j].rgbtRed + ogImage[i][j - 1].rgbtRed + ogImage[i][j + 1].rgbtRed
                + ogImage[i - 1][j].rgbtRed + ogImage[i - 1][j - 1].rgbtRed + ogImage[i - 1][j + 1].rgbtRed
                + ogImage[i + 1][j].rgbtRed + ogImage[i + 1][j - 1].rgbtRed + ogImage[i + 1][j + 1].rgbtRed) / 9.0);

                image[i][j].rgbtGreen = round((ogImage[i][j].rgbtGreen + ogImage[i][j - 1].rgbtGreen + ogImage[i][j + 1].rgbtGreen
                + ogImage[i - 1][j].rgbtGreen + ogImage[i - 1][j - 1].rgbtGreen + ogImage[i - 1][j + 1].rgbtGreen
                + ogImage[i + 1][j].rgbtGreen + ogImage[i + 1][j - 1].rgbtGreen + ogImage[i + 1][j + 1].rgbtGreen) / 9.0);

                image[i][j].rgbtBlue = round((ogImage[i][j].rgbtBlue + ogImage[i][j - 1].rgbtBlue + ogImage[i][j + 1].rgbtBlue
                + ogImage[i - 1][j].rgbtBlue + ogImage[i - 1][j - 1].rgbtBlue + ogImage[i - 1][j + 1].rgbtBlue
                + ogImage[i + 1][j].rgbtBlue + ogImage[i + 1][j - 1].rgbtBlue + ogImage[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }

    return;
}

// Blur image
/* void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // i = loop over every row
    for (int i = 0; i < height; i++)
    {
    // j = loop over every column
        for (int j = 0; j < width; j++)
        {
            // Array to stores values
            RGBTRIPLE value[9];

            float divideNum = 9;

            // Top row
            if (i == 0)
            {
                // Top left corner
                if (j == 0) {
                    value[0] = image[i][j + 1];
                    value[1] = image[i + 1][j + 1];
                    value[2] = image[i + 1][j];

                    divideNum = 4;
                }
                // Top right corner
                if (j == width - 1)
                {
                    value[0] = image[i + 1][j];
                    value[1] = image[i + 1][j - 1];
                    value[2] = image[i][j - 1];

                    divideNum = 4;
                }
                else if (i > 0 && j < width - 1)
                {
                    value[0] = image[i][j + 1];
                    value[1] = image[i + 1][j + 1];
                    value[2] = image[i + 1][j];
                    value[3] = image[i + 1][j - 1];
                    value[4] = image[i][j - 1];

                    divideNum = 5;
                }
            }
            // Bottom row
            else if (i == height - 1)
            {
                // Bottom left corner
                if (j == 0) {
                    value[0] = image[i - 1][j];
                    value[1] = image[i - 1][j + 1];
                    value[2] = image[i][j + 1];

                    divideNum = 4;
                }
                // Bottom right corner
                if (j == width - 1)
                {
                    value[0] = image[i - 1][j];
                    value[1] = image[i][j - 1];
                    value[2] = image[i - 1][j - 1];

                    divideNum = 4;
                }
                else if (j > 0 && j < width - 1)
                {
                    value[0] = image[i - 1][j];
                    value[1] = image[i][j - 1];
                    value[2] = image[i - 1][j - 1];
                    value[6] = image[i][j - 1];
                    value[7] = image[i - 1][j - 1];

                    divideNum = 5;
                }
            }
            // Left row
            else if ((j == 0 && i > 0) && (j == 0 && i < height - 1))
            {
                value[0] = image[i - 1][j];
                value[1] = image[i - 1][j + 1];
                value[2] = image[i][j + 1];
                value[3] = image[i + 1][j + 1];

                divideNum = 6;
            }
            // Right row
            else if ((j == height - 1 && i > 0) && (j == height - 1 && i < height - 1))
            {
                value[0] = image[i - 1][j];
                value[4] = image[i + 1][j];
                value[5] = image[i + 1][j - 1];
                value[6] = image[i][j - 1];
                value[7] = image[i - 1][j - 1];

                divideNum = 6;
            }
            else {
                value[0] = image[i - 1][j];
                value[1] = image[i - 1][j + 1];
                value[2] = image[i][j + 1];
                value[3] = image[i + 1][j + 1];
                value[4] = image[i + 1][j];
                value[5] = image[i + 1][j - 1];
                value[6] = image[i][j - 1];
                value[7] = image[i - 1][j - 1];

                divideNum = 9;
            }

            value[8] = image[i][j];

            // Calculate avg
            float avgBlue = 0.00;
            float avgGreen = 0.00;
            float avgRed = 0.00;

            for (int k = 0; k < 10; k++)
            {
                avgBlue += (float) value[k].rgbtBlue;
                avgGreen += (float) value[k].rgbtGreen;
                avgRed += (float) value[k].rgbtRed;
            }

            avgBlue = round(avgBlue / divideNum );
            avgGreen = round(avgGreen / divideNum );
            avgRed = round(avgRed / divideNum );

            // Set each pixel to average RGB
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
} */