#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

void get_sepia_color(RGBTRIPLE *pixel);
void blur_pixel(int height, int width, RGBTRIPLE temp[height][width], RGBTRIPLE image[height][width], int k, int l);
void edges(int height, int width, RGBTRIPLE image[height][width]);
int *get_Gx_Gy(int height, int width, RGBTRIPLE temp[height][width], int k, int l, char xy);
BYTE sobel_operator(int Gx, int Gy);

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
            get_sepia_color(&image[i][j]);
        }
    }

    return;
}

void get_sepia_color(RGBTRIPLE *pixel)
{
    BYTE originalBlue = pixel->rgbtBlue;
    BYTE originalGreen = pixel->rgbtGreen;
    BYTE originalRed = pixel->rgbtRed;

    double Blue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
    double Green = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
    double Red = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

    pixel->rgbtBlue = (Blue > 255) ? 255 : (BYTE)Blue;
    pixel->rgbtGreen = (Green > 255) ? 255 : (BYTE)Green;
    pixel->rgbtRed = (Red > 255) ? 255 : (BYTE)Red;
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
            int *Gx = get_Gx_Gy(height, width, temp, i, j, 'x');
            int *Gy = get_Gx_Gy(height, width, temp, i, j, 'y');

            image[i][j].rgbtBlue = sobel_operator(Gx[0], Gy[0]);
            image[i][j].rgbtGreen = sobel_operator(Gx[1], Gy[1]);
            image[i][j].rgbtRed = sobel_operator(Gx[2], Gy[2]);

            free(Gx);
            free(Gy);
        }
    }

    return;
}

int *get_Gx_Gy(int height, int width, RGBTRIPLE temp[height][width], int k, int l, char xy)
{
    int *G = malloc(3 * sizeof(int));

    int blue = 0;
    int green = 0;
    int red = 0;

    int offset[3][3];
    switch (xy)
    {
    case 'x':
        memcpy(offset, (int[3][3]){{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}, sizeof(offset));
        break;

    case 'y':
        memcpy(offset, (int[3][3]){{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}, sizeof(offset));
        break;
    }

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

    G[0] = blue;
    G[1] = green;
    G[2] = red;

    return G;
}

BYTE sobel_operator(int Gx, int Gy)
{
    double result = round(sqrt(Gx * Gx + Gy * Gy));

    return (result > 255) ? 255 : (BYTE)result;
}