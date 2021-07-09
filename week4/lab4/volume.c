// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

void cpyHeader(FILE *Input, FILE *Output, float factor);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    
    cpyHeader(input, output, factor);
    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}

void cpyHeader(FILE *Input, FILE *Output, float factor)
{
    uint8_t header[HEADER_SIZE];
    uint8_t headertst[HEADER_SIZE];
    int16_t buffer;
    
    fread(header, HEADER_SIZE, 1, Input);
    fwrite(header, HEADER_SIZE, 1, Output);

    while (fread(&buffer, sizeof(uint16_t), 1, Input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(uint16_t), 1, Output);
    }
}