#include <stdlib.h>
#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take the average of the RGB components of a pixel and store them into
            // a temporal variable, this variable is capable of storing decimals.
            buffer = (float)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // round up the decimal portion of the temporal variable.
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            // store the value of the temporal value into the RGB components of the pixel,
            // the decimal portion will be truncated by the casting (BYTE).
            image[i][j].rgbtRed = (BYTE)buffer;
            image[i][j].rgbtGreen = (BYTE)buffer;
            image[i][j].rgbtBlue = (BYTE)buffer;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*backup)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // create a backup for the image, this backup will be used to swap
    // the pixels from the original image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // invert the order of the pixels and store them in the backup image
            // i.e. the last pixel of the original image will be copied
            // into the first pixel of the backup image.
            backup[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            backup[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            backup[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue; 
        }
    }
    // copy the backup (and inversed) image back to the original array.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = backup[i][j].rgbtRed;
            image[i][j].rgbtGreen = backup[i][j].rgbtGreen;
            image[i][j].rgbtBlue = backup[i][j].rgbtBlue; 
        }
    }

    free(backup);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int pixelCounter;
    uint16_t tmpR, tmpG, tmpB;
    float buffer;
    RGBTRIPLE(*backup)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterate through every single pixel of the image... 
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixelCounter = 0;
            tmpR = 0;
            tmpG = 0;
            tmpB = 0;
            // Iterate through the sorrounding pixels...
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // consider the edges, if an edge is detected, don't increase
                    // the pixel counter (used for average)
                    if ((y + i >= 0) && (y + i < height))
                    {
                        if ((x + j >= 0) && (x + j < width))
                        {
                            // acumulate the value for the different components, RGB,
                            // of the "pixel in process"
                            pixelCounter++;
                            tmpR += image[y + i][x + j].rgbtRed;
                            tmpG += image[y + i][x + j].rgbtGreen;
                            tmpB += image[y + i][x + j].rgbtBlue;
                        }
                    }
                }
            }
            // calculate the average avalue for the red component.
            buffer = tmpR / (float)pixelCounter;
            // roundup the value of the average value.
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            // save only the integer portion of the rounded value.
            backup[y][x].rgbtRed = (BYTE)buffer;
            // do the same here for the green component...
            buffer = tmpG / (float)pixelCounter;
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            backup[y][x].rgbtGreen = (BYTE)buffer;
            // ...and for the blue as well
            buffer = tmpB / (float)pixelCounter;
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            backup[y][x].rgbtBlue = (BYTE)buffer;
        }
    }

    // copy the backup (and inversed) image back to the original array.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = backup[i][j].rgbtRed;
            image[i][j].rgbtGreen = backup[i][j].rgbtGreen;
            image[i][j].rgbtBlue = backup[i][j].rgbtBlue; 
        }
    }
    // free the reserved memory...
    free(backup);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int16_t tmpRx, tmpGx, tmpBx;
    int16_t tmpRy, tmpGy, tmpBy;
    float buffer;
    RGBTRIPLE(*backup)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // defining the sobel operator, Gx and Gy
    int8_t Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int8_t Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Iterate through every single pixel of the image... 
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tmpRx = 0;
            tmpGx = 0;
            tmpBx = 0;
            tmpRy = 0;
            tmpGy = 0;
            tmpBy = 0;
            // Iterate through the surrounding pixels
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if ((y + i >= 0) && (y + i < height))
                    {
                        if ((x + j >= 0) && (x + j < width))
                        {
                            // multiply the components of the 9 surrounding pixels 
                            // (including the center pixel) to the corresponding sobel
                            // operator value, the pixels surrounding the image (i.i. image[-1][-1])
                            // are considered black pixels {0,0,0}, therefore, there's no
                            // need for explicit muliplication, as any value multiplied by 0
                            // is equal to 0.
                            tmpRx += image[y + i][x + j].rgbtRed * Gx[i + 1][j + 1];
                            tmpGx += image[y + i][x + j].rgbtGreen * Gx[i + 1][j + 1];
                            tmpBx += image[y + i][x + j].rgbtBlue * Gx[i + 1][j + 1];
                            tmpRy += image[y + i][x + j].rgbtRed * Gy[i + 1][j + 1];
                            tmpGy += image[y + i][x + j].rgbtGreen * Gy[i + 1][j + 1];
                            tmpBy += image[y + i][x + j].rgbtBlue * Gy[i + 1][j + 1];
                        }
                    }
                }
            }
            /* The Sobel filter algorithm combines Gx and Gy into a final value by calculating 
            the square root of Gx^2 + Gy^2. And since channel values can only take on integer 
            values from 0 to 255, be sure the resulting value is rounded to the nearest integer 
            and capped at 255 */
            buffer = sqrt((tmpRx * tmpRx) + (tmpRy * tmpRy));
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            if (buffer > 255)
            {
                buffer = 255;
            }
            backup[y][x].rgbtRed = (BYTE)buffer;
            // the same principle applies to the green component...
            buffer = sqrt((tmpGx * tmpGx) + (tmpGy * tmpGy));
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            if (buffer > 255)
            {
                buffer = 255;
            }
            backup[y][x].rgbtGreen = (BYTE)buffer;
            // ...and for the blue as well.
            buffer = sqrt((tmpBx * tmpBx) + (tmpBy * tmpBy));
            if (buffer - (BYTE)buffer >= 0.5)
            {
                buffer += 1;
            } 
            if (buffer > 255)
            {
                buffer = 255;
            }
            backup[y][x].rgbtBlue = (BYTE)buffer;
        }
    }

    // copy the backup (and inversed) image back to the original array.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = backup[i][j].rgbtRed;
            image[i][j].rgbtGreen = backup[i][j].rgbtGreen;
            image[i][j].rgbtBlue = backup[i][j].rgbtBlue; 
        }
    }
    // free the reserved memory...
    free(backup);
}

