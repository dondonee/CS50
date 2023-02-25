#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the correct command-line arguments were provided and print an error message if not.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: filter [flag] infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Get file size and calculate the number of blocks.
    struct stat st;
    stat(infile, &st);
    const int N = st.st_size / 512;
}
