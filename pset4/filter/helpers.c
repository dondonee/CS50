#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

BYTE get_sepia_color(BYTE originalBlue, BYTE originalGreen, BYTE originalRed, char rgb);
void blur_pixel(int height, int width, RGBTRIPLE temp[height][width], RGBTRIPLE image[height][width], int k, int l);
void edges(int height, int width, RGBTRIPLE image[height][width]);
int *get_Gx(int height, int width, RGBTRIPLE temp[height][width], int k, int l);
int *get_Gy(int height, int width, RGBTRIPLE temp[height][width], int k, int l);
BYTE sobel_opetator(int Gx, int Gy);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double result;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = (BYTE)result;
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

    return (BYTE)round(result);
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
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, height * width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_pixel(height, width, temp, image, i, j);
        }
    }

    return;
}

void blur_pixel(int height, int width, RGBTRIPLE temp[height][width], RGBTRIPLE image[height][width], int k, int l)
{
    int count = 0;
    double blue = 0;
    double green = 0;
    double red = 0;

    for (int i = k - 1; i <= k + 1; i++)
    {
        if (i < 0 || i >= height)
        {
            continue;
        }

        for (int j = l - 1; j <= l + 1; j++)
        {
            if (j < 0 || j >= width)
            {
                continue;
            }

            blue += temp[i][j].rgbtBlue;
            green += temp[i][j].rgbtGreen;
            red += temp[i][j].rgbtRed;

            count++;
        }
    }

    blue = round(blue / count);
    green = round(green / count);
    red = round(red / count);

    image[k][l].rgbtBlue = (BYTE)blue;
    image[k][l].rgbtGreen = (BYTE)green;
    image[k][l].rgbtRed = (BYTE)red;

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, height * width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int *Gx = get_Gx(height, width, temp, i, j);
            int *Gy = get_Gy(height, width, temp, i, j);

            image[i][j].rgbtBlue = sobel_opetator(Gx[0], Gy[0]);
            image[i][j].rgbtGreen = sobel_opetator(Gx[1], Gy[1]);
            image[i][j].rgbtRed = sobel_opetator(Gx[2], Gy[2]);

            free(Gx);
            free(Gy);
        }
    }

    return;
}

int *get_Gx(int height, int width, RGBTRIPLE temp[height][width], int k, int l)
{
    int *Gx = malloc(3 * sizeof(int));

    int blue = 0;
    int green = 0;
    int red = 0;

    int offset[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int x = 0;

    for (int i = k - 1; i <= k + 1; i++)
    {
        int y = 0;

        for (int j = l - 1; j <= l + 1; j++)
        {
            if (i < 0 || i >= height)
            {
                break;
            }

            if (j < 0 || j >= width)
            {
                y++;
                continue;
            }

            blue += temp[i][j].rgbtBlue * offset[x][y];
            green += temp[i][j].rgbtGreen * offset[x][y];
            red += temp[i][j].rgbtRed * offset[x][y];

            y++;
        }

        x++;
    }

    Gx[0] = blue;
    Gx[1] = green;
    Gx[2] = red;

    return Gx;
}

int *get_Gy(int height, int width, RGBTRIPLE temp[height][width], int k, int l)
{
    int *Gy = malloc(3 * sizeof(int));

    int blue = 0;
    int green = 0;
    int red = 0;

    int offset[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int x = 0;

    for (int i = k - 1; i <= k + 1; i++)
    {
        int y = 0;

        for (int j = l - 1; j <= l + 1; j++)
        {
            if (i < 0 || i >= height)
            {
                break;
            }

            if (j < 0 || j >= width)
            {
                y++;
                continue;
            }

            blue += temp[i][j].rgbtBlue * offset[x][y];
            green += temp[i][j].rgbtGreen * offset[x][y];
            red += temp[i][j].rgbtRed * offset[x][y];

            y++;
        }

        x++;
    }

    Gy[0] = blue;
    Gy[1] = green;
    Gy[2] = red;

    return Gy;
}

BYTE sobel_opetator(int Gx, int Gy)
{
    double result = round(sqrt(Gx * Gx + Gy * Gy));

    if (result > 255)
    {
        return (BYTE)255;
    }
    else if (result < 0)
    {
        return (BYTE)0;
    }

    return (BYTE)result;
}