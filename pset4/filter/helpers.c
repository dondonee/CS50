#include "helpers.h"
#include <math.h>
#include <string.h>

BYTE get_sepia_color(BYTE originalBlue, BYTE originalGreen, BYTE originalRed, char rgb);
void blur_pixel(int height, int width, RGBTRIPLE image[height][width], int k, int l);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double rgb_sum;
    BYTE result;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgb_sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            result = (BYTE)(round(rgb_sum / 3));

            image[i][j].rgbtBlue = result;
            image[i][j].rgbtGreen = result;
            image[i][j].rgbtRed = result;
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
            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = get_sepia_color(originalBlue, originalGreen, originalRed, 'b');
            image[i][j].rgbtGreen = get_sepia_color(originalBlue, originalGreen, originalRed, 'g');
            image[i][j].rgbtRed = get_sepia_color(originalBlue, originalGreen, originalRed, 'r');
        }
    }

    return;
}

BYTE get_sepia_color(BYTE originalBlue, BYTE originalGreen, BYTE originalRed, char rgb)
{
    double result;
    switch (rgb)
    {
    case 'b':
        result = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
        break;

    case 'g':
        result = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
        break;

    case 'r':
        result = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
        break;
    }

    if (round(result) > 255)
    {
        return (BYTE)255;
    }

    return (BYTE)result;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, height * width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][width - j - 1];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_pixel(height, width, image, i, j);
        }
    }

    return;
}

void blur_pixel(int height, int width, RGBTRIPLE image[height][width], int k, int l)
{
    int count = 0;
    int blue = 0;
    int green = 0;
    int red = 0;

    for (int i = k - 1; i <= k + 1; i++)
    {
        if (i < 0 || i > height)
        {
            continue;
        }

        for (int j = l - 1; j <= l + 1; j++)
        {
            if (j < 0 || j > width)
            {
                continue;
            }

            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            red += image[i][j].rgbtRed;

            count++;
        }
    }

    image[k][l].rgbtBlue = round(blue / count);
    image[k][l].rgbtGreen = round(green / count);
    image[k][l].rgbtRed = round(red / count);

    return;
}
