#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
      for (int i = 0; i<height;i++)
    {
        for (int b = 0; b<width;b++)
        {
            float avrg = ((image[i][b].rgbtBlue + image[i][b].rgbtRed + image[i][b].rgbtGreen) / 3);
            int avrground = round(avrg);

            image[i][b].rgbtRed = avrground;
            image[i][b].rgbtBlue = avrground;
            image[i][b].rgbtGreen = avrground;
        }
    }
    return;

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

      for (int i = 0; i<height;i++)
    {
        for (int b = 0; b<width;b++)
        {
            int SepiaRed = round(.393*image[i][b].rgbtRed + .769*image[i][b].rgbtBlue + .189*image[i][b].rgbtGreen);
            int SepiaBlue = round(.272*image[i][b].rgbtRed + .534*image[i][b].rgbtBlue + .131*image[i][b].rgbtGreen);
            int SepiaGreen = round(.349*image[i][b].rgbtRed + .686*image[i][b].rgbtBlue + .168*image[i][b].rgbtGreen);
            {
                if (SepiaRed > 255)
                {
                    SepiaRed = 255;
                }
                if (SepiaBlue  > 255)
                {
                    SepiaBlue = 255;
                }
                if (SepiaGreen > 255)
                {
                    SepiaGreen = 255;
                }

            }
            image[i][b].rgbtRed = SepiaRed;
            image[i][b].rgbtBlue = SepiaBlue;
            image[i][b].rgbtGreen = SepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height;i++)
    {
        for(int b = 0; b<width / 2; b++)
        {
            RGBTRIPLE temp = image[i][b];
            image[i][b] = image[i][width - (b+1)];
            image[i][width-(b+1)] = temp;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int b = 0; b < width; b++)
        {
            float red = 0;
            float blue = 0;
            float green = 0;
            float total = 0;

            for (int j = -1; j < 2; j++)
            {
                for (int z = -1; z < 2; z++)
                {
                    int row = i + j;
                    int col = b + z;
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        red += image[row][col].rgbtRed;
                        green += image[row][col].rgbtGreen;
                        blue += image[row][col].rgbtBlue;
                        total++;
                    }
                }
            }

            temp[i][b].rgbtRed = round(red / total);
            temp[i][b].rgbtGreen = round(green / total);
            temp[i][b].rgbtBlue = round(blue / total);
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int h = 0; h < width; h++)
        {
            image[y][h] = temp[y][h];
        }
    }
}
