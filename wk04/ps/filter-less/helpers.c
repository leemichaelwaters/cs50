#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculatae average
            avg_pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // set pixel to average
            image[i][j].rgbtBlue = avg_pixel;
            image[i][j].rgbtGreen = avg_pixel;
            image[i][j].rgbtRed = avg_pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int new_red, new_green, new_blue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate sepia value
            new_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            new_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            new_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // set pixel to sepia
            if (new_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = new_red;
            }

            if (new_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = new_green;
            }

            if (new_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = new_blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            // top row
            if (i == 0)
            {
                // top left corner
                if (j == 0)
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                image[i + 1][j].rgbtRed) / 4.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                  image[i + 1][j].rgbtGreen) / 4.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                                 image[i + 1][j].rgbtBlue) / 4.0);
                }
                // top right corner
                else if (j == (width - 1))
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                                image[i][j - 1].rgbtRed) / 4.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                  image[i][j - 1].rgbtGreen) / 4.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                 image[i][j - 1].rgbtBlue) / 4.0);
                }
                // top middle row
                else
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                  image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                                 image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0);
                }
            }
            // bottom row
            else if (i == (height - 1))
            {
                // bottom left corner
                if (j == 0)
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                                image[i - 1][j + 1].rgbtRed) / 4.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                  image[i - 1][j + 1].rgbtGreen) / 4.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                 image[i - 1][j + 1].rgbtBlue) / 4.0);

                }
                // bottom right corner
                else if (j == (width - 1))
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                                image[i - 1][j].rgbtRed) / 4.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                                  image[i - 1][j].rgbtGreen) / 4.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                 image[i - 1][j].rgbtBlue) / 4.0);

                }
                // bottom middle row
                else
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                                image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                  image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                 image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                }
            }
            // middle rows
            else
            {
                // left side
                if (j == 0)
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                  image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                                 image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                }
                // right side
                else if (j == (width - 1))
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                                image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed) / 6.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                  image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) / 6.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                 image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) / 6.0);
                }
                // middle
                else
                {
                    copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed +
                                                image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9.0);
                    copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                  image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                  image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.0);
                    copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                                 image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                 image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.0);
                }
            }
        }
    }

    // blur image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}