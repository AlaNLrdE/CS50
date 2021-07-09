#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

const uint8_t JPEGpattern[3] = {0xff, 0xd8, 0xff};
const uint16_t blockSize = 512;

void recoverImgs(FILE *inputFile);
void fileNameGenerator(char *output, int index);

int main(int argc, char *argv[])
{
    int iRet = 0;
    // Check for invalid usage
    if (argc != 2)
    {
        // teach the user the correct usage of the program,
        // if the program is not invoked with exactly one parameter
        printf("Usage: ./recover image\n");
        iRet = 1;
    }
    else
    {
        // validate the raw input
        FILE *rawFile = fopen(argv[1], "r");
        if (rawFile == NULL)
        {
            printf("Could not open file.\n");
            iRet = 1;
        }
        else
        {
            recoverImgs(rawFile);
        }
        fclose(rawFile);
    }

    return iRet;
}

void recoverImgs(FILE *inputFile)
{
    uint16_t noOfImagesFound = 0;
    uint16_t blockID = 0;
    uint32_t imageRawHeader[100][2];
    uint16_t imageLenght = 0; // lenght in number of blocks
    char filename[8];
    BYTE *buffer = (BYTE *)calloc(blockSize, sizeof(BYTE));

    if (buffer == NULL)
    {
        exit(1);
    } 
    else
    {
        /* this section of the function creates an array to store the image location and lenght
         - because the memory is read in blocks of 512 bytes, the location points to the block 
         containing the JPG pattern 0xff 0xd8 0xff */ 
        while (fread(buffer, sizeof(BYTE), blockSize, inputFile))
        {
            if (buffer[0] == JPEGpattern[0] && buffer[1] == JPEGpattern[1] && buffer[2] == JPEGpattern[2])
            {
                if (noOfImagesFound > 0)
                {
                    /* the length is calculated in multiples of blocks, for example:
                    if one img is found in block 2 and the next img is found in block 6,
                    that means that the block size is 4, remember that the images are
                    stored one after the other and that the img header pattern is always stored
                    at the beginning the block */
                    imageLenght = blockID - imageRawHeader[noOfImagesFound - 1][0];
                    imageRawHeader[noOfImagesFound - 1][1] = imageLenght;
                }
                imageRawHeader[noOfImagesFound][0] = blockID;
                noOfImagesFound++;
            }
            blockID++;
        }
        if (noOfImagesFound > 0)
        {
            imageLenght = blockID - imageRawHeader[noOfImagesFound - 1][0];
            imageRawHeader[noOfImagesFound - 1][1] = imageLenght;
        }
    }
    // re-position the pointer of the file to the beggining
    fseek(inputFile, blockSize * imageRawHeader[0][0], SEEK_SET);

    /* this portion of the program iterates trough the total number of found images, allocate/reallocate
    enough memory to create the output file. Because now we know the size of the image (how many numbers of
    blocks uses), we can read the entire image from the raw input file and write it into the output ###.jpg */
    for (int imgIndex = 0; imgIndex < noOfImagesFound; imgIndex++)
    {
        // filename will have the format ###.jpg
        fileNameGenerator(filename, imgIndex);
        // allocates memory to store the picture pixels
        buffer = (BYTE *)realloc(buffer, blockSize * imageRawHeader[imgIndex][1]);
        FILE *picture = fopen(filename, "w");
        // read from the raw input, the size is calculated multiplying the size of the picture in blocks and the block size
        fread(buffer, sizeof(BYTE), blockSize * imageRawHeader[imgIndex][1], inputFile);
        // store the picture in ###.jpg
        fwrite(buffer, sizeof(BYTE), blockSize * imageRawHeader[imgIndex][1], picture);
        fclose(picture);
    }
    free(buffer);
}

void fileNameGenerator(char *output, int index)
{
    // this function "creates" the name of the file with the format ###.jpg
    for (int i = 2; i >= 0; i--)
    {
        output[i] = (index % 10) + 48;
        index = index / 10;
    }

    // appends the file extension
    output[3] = '.';
    output[4] = 'j';
    output[5] = 'p';
    output[6] = 'g';
    output[7] = '\0';
}

