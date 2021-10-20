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

// Function Prototypes
void set_edge_effect(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE image_copy[height][width]);
int calculate_Gx(int i, int j, int height, int width, RGBTRIPLE image[height][width], int c);
int calculate_Gy(int i, int j, int height, int width, RGBTRIPLE image[height][width], int c);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the real image
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // Set edge effect for each pixel using copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            set_edge_effect(i, j, height, width, image, image_copy);
        }
    }
    return;
}

// Function definations
void set_edge_effect(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE image_copy[height][width])
{
    int gx, gy, rgb[3];

    for (int c = 0; c < 3; ++c)
    {
        // Calculating gx and gy
        gx = calculate_Gx(i, j, height, width, image_copy, c);
        gy = calculate_Gy(i, j, height, width, image_copy, c);

        // normalizing result
        rgb[c] = round(pow((pow(gx, 2) + pow(gy, 2)), .5));

        // No change
        if (rgb[c] == 0)
        {
            continue;
        }

        if (rgb[c] >= 255)
        {
            rgb[c] = 255;
        }

        // Set new value to corresponding color
        if (c == 0)
        {
            image[i][j].rgbtRed = rgb[c];
        }
        else if (c == 1)
        {
            image[i][j].rgbtGreen = rgb[c];
        }
        else
        {
            image[i][j].rgbtBlue = rgb[c];
        }
    }
}

int calculate_Gx(int i, int j, int height, int width, RGBTRIPLE image[height][width], int c)
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    // Product of gx matrix with pixel grid
    for (int x = i - 1, x1 = 0; x <= i + 1; x++, x1++)
    {
        for (int y = j - 1, y1 = 0; y <= j + 1; y++, y1++)
        {
            // Pixel is out of image
            if (x < 0 || x >= height || y < 0 || y >= width)
            {
                gx[x1][y1] = 0;
                continue;
            }

            // make calculation for gx based on color, c[red, green, blue]
            if (c == 0)
            {
                gx[x1][y1] *= image[x][y].rgbtRed;
            }
            else if (c == 1)
            {
                gx[x1][y1] *= image[x][y].rgbtGreen;
            }
            else
            {
                gx[x1][y1] *= image[x][y].rgbtBlue;
            }
        }
    }

    int sum = 0;

    // Summing gx matrix elements
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sum += gx[x][y];
        }
    }

    return sum;
}

int calculate_Gy(int i, int j, int height, int width, RGBTRIPLE image[height][width], int c)
{
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Product of gy matrix with pixel grid
    for (int x = i - 1, x1 = 0; x <= i + 1; x++, x1++)
    {
        for (int y = j - 1, y1 = 0; y <= j + 1; y++, y1++)
        {
            // no pixel there
            if (x < 0 || x >= height || y < 0 || y >= width)
            {
                gy[x1][y1] = 0;
                continue;
            }

            // make calculation for gy based on color, c[red, green, blue]
            if (c == 0)
            {
                gy[x1][y1] *= image[x][y].rgbtRed;
            }
            else if (c == 1)
            {
                gy[x1][y1] *= image[x][y].rgbtGreen;
            }
            else
            {
                gy[x1][y1] *= image[x][y].rgbtBlue;
            }
        }
    }

    int sum = 0;

    // Summing gx matrix elements
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sum += gy[x][y];
        }
    }

    return sum;
}