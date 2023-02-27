#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

bool isJPEG(FILE *file);
void copy_block(FILE *inptr, FILE *outptr);

int main(int argc, char *argv[])
{
    // Check if the correct command-line arguments were provided and print an error message if not.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: filter [flag] infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Get file size and calculate the number of blocks.
    fseek(inptr, 0, SEEK_END);
    const int N = ftell(inptr) / BLOCK_SIZE;

    // Read each 512-byte block of the input file
    int fileCnt = 0;
    char outfile[8];
    FILE *outptr = NULL;

    for (int i = 0; i < N; i++)
    {
        fseek(inptr, BLOCK_SIZE * i, SEEK_SET);

        // If the current block contains the start of a JPEG file, create a new file to write the recovered JPEG data to.
        if (isJPEG(inptr))
        {
            sprintf(outfile, "%03i.jpg", fileCnt++);
            outptr = fopen(outfile, "a");
        }

        if (fileCnt > 0)
        {
            copy_block(inptr, outptr);
        }
    }

    fclose(outptr);
}

bool isJPEG(FILE *file)
{
    BYTE start_bytes[4];
    fread(&start_bytes, 1, 4, file);
    fseek(file, -4, SEEK_CUR);

    if (start_bytes[0] == 0xff && start_bytes[1] == 0xd8 && start_bytes[2] == 0xff && (start_bytes[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}

void copy_block(FILE *inptr, FILE *outptr)
{
    BYTE buffer[BLOCK_SIZE];
    fread(buffer, 1, BLOCK_SIZE, inptr);
    fwrite(buffer, 1, BLOCK_SIZE, outptr);
}
