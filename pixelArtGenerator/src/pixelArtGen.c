#include <stdio.h>
#include <string.h>
#include "image.h"

int main(int argc, char **argv)
{
    image originalImage;
    uint8_t withGrayScale = 0;
    
    //Nearest Neighbor Resizing
    printf("Generating image...\n");
    if(argc < 4)
    {
        printf("usage: %s [8bit | 16bit] [(integer)ResizeFactor] inputImage (optional)withGrayScale\n", argv[0]); 
        printf("Example: %s 8bit 3 pics/maiden3.jpg withGrayScale", argv[0]);
        return 1; 
    } 
    else 
    {
        originalImage = load_image(argv[3]);
        if (argc >= 5)
        {
            withGrayScale = 1;
        }
    }

    if (0 == strcmp(argv[1], "8bit"))
    {     
        pixelTransformation(originalImage, atoi(argv[2]), filterMode_8bit, withGrayScale);
    }
    else if (0 == strcmp(argv[1], "16bit"))
    {
        pixelTransformation(originalImage, atoi(argv[2]), filterMode_16bit, withGrayScale);
    }

    return 0;
}
