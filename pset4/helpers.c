#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates average of values
            avg = (int) round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Set RGB values as average
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
    // Formulae to used
    // sepiaRed   = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue  = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

    // temporary variables used for storing values to do calculation
    int originalRed, originalGreen, originalBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy original values
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // Calculating Red value
            if (round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            }


            // Calculating Green value
            if (round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            }

            // Calculating Blue value
            if (round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable used for swaping colors
    int temp;

    for (int i = 0; i < height; i++)
    {
        // Iterate two variables, one from start to middle, and other from end to middle.
        for (int j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            // Swap Red colors
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = temp;

            // Swap Green colors
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = temp;

            // Swap Bed colors
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Stores average of colors, avgRGB[0] for Red, avgRGB[1] for Green and avgRGB[2] for Blue
    int avgRGB[3];

    // Stores total cells to consider while making average
    int countCells;

    // Make a copy of the real image
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset all to 0
            avgRGB[0] = avgRGB[1] = avgRGB[2] = countCells = 0;

            // Add up pixel color to average
            for (int x = i - 1; x <= i + 1; x++)
            {
                if (x < 0 || x >= height)
                {
                    continue;
                }

                for (int y = j - 1; y <= j + 1; y++)
                {
                    // no pixel there
                    if (y < 0 || y >= width)
                    {
                        continue;
                    }

                    // adds up current colors in average and increment countcells
                    avgRGB[0] += image_copy[x][y].rgbtRed;
                    avgRGB[1] += image_copy[x][y].rgbtGreen;
                    avgRGB[2] += image_copy[x][y].rgbtBlue;

                    countCells++;
                }
            }

            // Divide average by total cells added
            for (int a = 0; a < 3; a++)
            {
                avgRGB[a] = (int)round(((float)avgRGB[a]) / countCells);
            }

            // Set average colors value to pixel
            image[i][j].rgbtRed = avgRGB[0];
            image[i][j].rgbtGreen = avgRGB[1];
            image[i][j].rgbtBlue = avgRGB[2];
        }
    }

    return;
}