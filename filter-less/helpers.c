#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;

            int sepiaRed =
                mini(255, round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen =
                mini(255, round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue =
                mini(255, round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE left_pixel = image[i][j];
            RGBTRIPLE right_pixel = image[i][width - j - 1];

            image[i][j] = right_pixel;
            image[i][width - j - 1] = left_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Row loop
    for (int i = 0; i < height; i++)
    {
        // "pixel" loop
        for (int j = 0; j < width; j++)
        {
            // RGBTRIPLE mid_average = {0, 0, 0};
            // RGBTRIPLE bot_average = {0, 0, 0};
            RGBTRIPLE top_average = {0, 0, 0};

            if (i - 1 >= 0)
            {
                top_average = average_row(maxi(0, j - 1), 3, image[i - 1]);
            }

            int red_average = round(top_average.rgbtRed / 3.0);

            RGBTRIPLE new_pixel = { top_average.rgbtBlue, top_average.rgbtGreen, red_average };
        }
    }
    return;
}

int mini(int a, int b)
{
    if (a > b)
    {
        return b;
    }

    return a;
}

int maxi(int a, int b)
{
    if (a < b)
    {
        return b;
    }

    return a;
}

RGBTRIPLE average_row(int start, int length, RGBTRIPLE image[])
{
    RGBTRIPLE pixel_average;// = 0;

    int red_sum = 0;
    int green_sum = 0;
    int blue_sum = 0;

    for (int n = start; n < start + length; n++)
    {
        red_sum += image[n].rgbtRed;
        green_sum += image[n].rgbtGreen;
        blue_sum += image[n].rgbtBlue;
    }

    pixel_average.rgbtRed = round(red_sum / 3.0);
    pixel_average.rgbtGreen = round(green_sum / 3.0);
    pixel_average.rgbtBlue = round(blue_sum / 3.0);

    return pixel_average;
}
